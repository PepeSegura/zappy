#include "TCPServer.hpp"

TCPServer::TCPServer(int port, Game &game): game(game), players(game.get_players_map()){

	createBindSocket(port);

	addToPoll(socketFd, POLLIN);

	std::cout << "Server listening on port " << port << std::endl;
}

TCPServer::~TCPServer() {
	for (size_t i = 0; i < pollFds.size(); i++) {
		if (socketFd != pollFds[i].fd)
			close(pollFds[i].fd);
	}
	if (socketFd != -1) {
		close(socketFd);
	}
}

void	TCPServer::inputOutputComms() { //manages network comms with clients through buffers
	int	pollRet = poll(pollFds.data(), pollFds.size(), 0);
	if (pollRet == -1)
	{
		std::cerr << "Error: server: error in POLL.\n";
		exit(EXIT_FAILURE);
	}
	else if (pollRet == 0)
	{
		//std::cout << "Poll timeout. No events\n";
	} else {
		players = game.get_players_map();
		for (size_t i = 0; i < pollFds.size(); i++) {
			if (pollFds[i].revents & POLLIN) { //read event
				if (pollFds[i].fd == socketFd) { //new connection
					acceptClient();
				} else { //received client message
					readClientData(&i);
				}
			} else if (pollFds[i].revents & POLLOUT){ //write event
				if (players[pollFds[i].fd] && players[pollFds[i].fd]->get_send_buffer().length()) {
					send(pollFds[i].fd, players[pollFds[i].fd]->get_send_buffer().c_str(), players[pollFds[i].fd]->get_send_buffer().length(), 0);
					players[pollFds[i].fd]->set_send_buffer("");
					if (players[pollFds[i].fd]->get_dead()) { //player is dead and has been notified, remove him!!!
						disconnectClient(&i);
					}
				}
			}
			usleep(500);
		}
	}
}

void	TCPServer::acceptClient() {
	int clientFd = accept(socketFd, NULL, NULL);
					
	if (clientFd < 0) {
		perror("accept");
		return ;
	}
	if (pollFds.size() < MAX_CLIENTS) {
		addToPoll(clientFd, POLLIN | POLLOUT);	
		std::cout << "Client with fd " << clientFd << " accepted.\n";
		game.add_player_to_fdmap(clientFd, new Player(&this->game));
		players = game.get_players_map();
		players[clientFd]->set_sock_fd(clientFd);
		std::string tmp = "BIENVENUE\n";
		players[clientFd]->set_send_buffer(tmp);
		return ;
	}
	std::cerr << "Error: server: too many clients.\n";
	close(clientFd);
}

void	TCPServer::readClientData(size_t *idx) {
	char	buffer[4096];
					
	memset(buffer, 0, sizeof(buffer));
	int readBytes = recv(pollFds[*idx].fd, buffer, sizeof(buffer) - 1, 0);

	if (readBytes < 0) { //closed
		std::cerr << "Error: server: Socket " << pollFds[*idx].fd << " is closed.\n";
		disconnectClient(idx);
	} else if (readBytes == 0) { //disconnected
		disconnectClient(idx);
	} else { //data received
		// std::cout << "Received from clientFd " << pollFds[*idx].fd << ": [[" << buffer << "]]\n";
		players[pollFds[*idx].fd]->add_buffer_or_parse_msg(std::string(buffer));
		// players[pollFds[*idx].fd]->set_recv_buffer(tmp);
	}
}

void	TCPServer::disconnectClient(size_t *idx) {
	std::cout << "Client " << pollFds[*idx].fd << " disconnected.\n";
	game.remove_player(game.get_players_map()[pollFds[*idx].fd]);
	close(pollFds[*idx].fd);
	poll_iterator it_poll = pollFds.begin();
	pollFds.erase(it_poll + *idx);
	--(*idx);
}

void	TCPServer::createBindSocket(int port) { //create and configure socket
	socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFd == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	int reuse = 1;
	if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse, sizeof(reuse)) < 0)
	{
		perror("setsockopt(SO_REUSEADDR)");
		exit(EXIT_FAILURE);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	std::string hostname = "127.0.0.1";
	if (inet_aton(hostname.c_str(), &server_addr.sin_addr) == 0) {
		std::cerr << "Invalid address/Address not supported: " << hostname << std::endl;
		exit(EXIT_FAILURE);
	}

	//upon successful socket creation, bind and start listening

	if (bind(socketFd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if (listen(socketFd, 16) == -1)
	{
		perror("Listening failed");
		exit(EXIT_FAILURE);
	}
}

void	TCPServer::addToPoll(int fd, int flags) {
	pollfd	tmp;

	tmp.fd = fd;
	tmp.events = flags;

	pollFds.push_back(tmp);
}
