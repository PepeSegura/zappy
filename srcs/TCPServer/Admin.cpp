#include "TCPServer.hpp"

void	TCPServer::addAdminToPoll() {
	int	fd = STDIN_FILENO;
	addToPoll(fd, POLLIN | POLLNVAL);	
	game.add_player_to_fdmap(fd, new Player(&this->game));
	players = game.get_players_map();
	players[fd]->set_sock_fd(fd);
}

void TCPServer::processAdminCommand(const std::string& command) {
	std::istringstream iss(command);
	std::string cmd;
	iss >> cmd;
	
	if (cmd == "help") {
		std::cerr << "Available admin commands:" << std::endl;
		std::cerr << "  help  - Show this help" << std::endl;
		std::cerr << "  info  - List connected players info" << std::endl;
		std::cerr << "  debug - Show/Hide stdout - on/off" << std::endl;
		std::cerr << "  time  - Modify time unit 1-1000" << std::endl;
	} else if (cmd == "debug") {
		std::string mode;
		
		if (iss >> mode) {
			if (mode == "off") {
				if (freopen("/dev/null", "w", stdout) == NULL) {
					perror("freopen");
				} else {
					std::cerr << "Debug output disabled" << std::endl;
					std::cout.flush();
				}
			} else if (mode == "on") {
				if (freopen("/dev/tty", "w", stdout) == NULL) {
					int new_stdout = dup2(STDERR_FILENO, STDOUT_FILENO);
					if (new_stdout == -1) {
						perror("Failed to restore stdout");
					}
				}
				std::cerr << "Debug output enabled" << std::endl;
			} else {
				std::cerr << "Usage: debug on/off" << std::endl;
			}
		}
	} else if (cmd == "info") {

		std::cerr << (
			(this->game.get_debug() == true) ? ("Debug mode: ENABLED - Cmd queue size: " + std::to_string(QUEUE_SIZE_DBG) + " - Players stay alive without food") : ("Debug mode: DISABLED - Cmd queue size: " + std::to_string(QUEUE_SIZE))
		) << std::endl << std::endl;

		std::cerr << "Active connections (" << players.size() << "):" << std::endl;
		for (const auto& pair : players) {
			int fd = pair.first;
			int state = pair.second->get_state();
			bool gr_client = pair.second->is_graphic_client();
			std::string type = ((fd == 0) ? "Admin" : (gr_client == true) ? "Graphic" : (state == Player_States::Handshake) ? "Wating for handshake" : "Player");

			std::cerr << "  FD " << fd
					  << "\t - Type: " << type
					  << ((type == "Player") ? ("\n\t - Team: " + pair.second->get_team_name()) : "")
					  << ((type == "Player") ? ("\n\t - Dir:  " + std::string(1, pair.second->get_dir())) : "")
					  << ((type == "Player") ? ("\n\t - Pos:  (" + std::to_string(pair.second->get_x()) + "," + std::to_string(pair.second->get_y()) + ")") : "");
			
			if (type == "Player") {
				Inventory &inv = pair.second->get_inv();
				std::cerr << "\n\t ------------- "
						  << "\n\t - Nourriture: " << inv.get_nourriture()
						  << "\n\t - Linemate:   " << inv.get_linemate()
						  << "\n\t - Deraumere:  " << inv.get_deraumere()
						  << "\n\t - Sibur:      " << inv.get_sibur()
						  << "\n\t - Mendiane:   " << inv.get_mendiane()
						  << "\n\t - Phiras:     " << inv.get_phiras()
						  << "\n\t - Thystame:   " << inv.get_thystame();
			}
					  
			std::cerr << "\n--------------------------------" << std::endl;

		}
	} else if (cmd == "time") {
		uint64_t time_mod;
		if (iss >> time_mod) {
			uint64_t old_time = this->game.get_tick_millis();
			if (time_mod != old_time) {
				this->game.set_tick_millis(time_mod);
				this->game.send2grclients(this->game.gr_time_unit());
				std::cerr << "New time: " << time_mod << std::endl;
			} else {
				std::cerr << "Same time as before: " << time_mod << std::endl;
			}
		} else {
			std::cerr << "There was an error. Current time: " << this->game.get_tick_millis() << std::endl;
		}
	} else {
		std::cerr << "Unknown command: " << cmd << ". Type 'help' for available commands." << std::endl;
	}
}

bool	TCPServer::readAdminData(size_t *idx) {
	char	buffer[4096];
					
	memset(buffer, 0, sizeof(buffer));
	int readBytes = read(pollFds[*idx].fd, buffer, sizeof(buffer) - 1);

	if (readBytes <= 0) { // Ctrl + D
		std::cout << "Closing server\n";
		this->game.set_end(true);
		return false;
	} else { //data received
		std::string command(buffer);

		command.erase(0, command.find_first_not_of(" \t\n\r\f\v"));
		command.erase(command.find_last_not_of(" \t\n\r\f\v") + 1);
		processAdminCommand(command);
	}
	return true;
}
