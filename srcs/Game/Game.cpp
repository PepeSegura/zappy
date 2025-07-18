#include "Game.hpp"

Game::Game()
{
}

Game::~Game() {
	for (auto& [fd, p] : playersfd_map) {
		if (p)
			delete p;
	}

	playersfd_map.clear();
}

std::map<int, Player *> &Game::get_players_map() {
	return this->playersfd_map;
}

void	Game::add_player_to_fdmap(int fd, Player *player) {
	playersfd_map.insert_or_assign(fd, player);
}

void Game::init_map(Parser *parser)
{
	int width  = parser->getWidth();
	int height = parser->getHeight();

	this->map.reserve(height);
	for (int i = 0; i < height; ++i)
		this->map.emplace_back(width);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			this->map[i][j].gen_resources();
			this->world_resources = this->world_resources + this->map[i][j].get_inv();
		}
	}
	std::cout << "Total World resources\n" << this->world_resources;
}

void Game::init_teams(Parser *parser)
{
	t_teams_names teamNames = parser->getTeamsNames();

	for (const auto& name : teamNames) {
		this->teams[name] = Team(name, parser->getTeamsMembersLimit());
		this->teams[name].init_eggs(parser->getTeamsMembersLimit(), parser->getHeight(), parser->getWidth());
	}
}

void Game::init_action_time_map() {
	action_time_table[Avance] = 7;
	action_time_table[Droite] = 7;
	action_time_table[Gauche] = 7;
	action_time_table[Voir] = 7;
	action_time_table[Inventaire] = 1;
	action_time_table[Prend] = 7;
	action_time_table[Pose] = 7;
	action_time_table[Expulse] = 7;
	action_time_table[Broadcast] = 7;
	action_time_table[IncantationBgn] = 300;
	action_time_table[IncantationEnd] = 0;
	action_time_table[Fork] = 42;
	action_time_table[ConnectNbr] = 0;
	action_time_table[Mort] = 0;
	action_time_table[Unknown] = 0;
}

Game::Game(Parser *parser)
{
	init_map(parser);
	init_teams(parser);
	init_action_time_map();
	
	end = false;
	tick_millis = 1000 / parser->getTimeFreq();
	// for (const auto& [name, team] : teams) {
	// 	std::cout << name << " -> " << team.get_name() << std::endl;
	// }
}

void Game::add_player_to_team(std::string team_name, Player *p)
{
	if (this->teams.find(team_name) == teams.end())
		return ;
	this->teams[team_name].add_player(p);
}

void Game::remove_player(Player *p)
{
	if (playersfd_map.find(p->get_sock_fd()) != playersfd_map.end())
		playersfd_map.erase(p->get_sock_fd());

	//remove player from tile
	
	for (auto& [name, team] : teams)
		team.remove_player(p);
	
	delete p;
	//std::cout << "Player deleted\n";
}

bool Game::get_end() const {
	return this->end;
}

void Game::run_tick() {
	auto now = std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	auto curr_millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	if (curr_millis - last_tick >= tick_millis) { //enough time has passed, run tick logic
		//std::cout << std::to_string(curr_millis) << std::endl;
		for (auto& [fd, player] : playersfd_map) { // for each team
			if (player->get_state() == Player_States::Free) {
				if (player->has_queued_actions()) {
					player->set_last_start_time(curr_millis);
					player->set_state(Player_States::ExecutingAction);
				}
			}
			if (player->get_state() == Player_States::ExecutingAction) {
				if (action_time_table[player->get_current_command().cmd] >= player->get_last_start_time() - curr_millis) { //action ended, call handlers
					std::cout << "Call handler :P\n";
				}
				continue; 
			}
			if (player->get_state() == Player_States::Handshake) {
				try2handshake(player);
			}
		}
		last_tick = curr_millis; // update last_tick timestamp
	}
}

void	Game::set_tick_millis(int64_t t) {
	if (t < 1 || t > 1000) {
		std::cerr << "Invalid freq; allowed values [1, 1000]\n";
		return ;
	}
	this->tick_millis = 1000 / t;
}

void	Game::try2handshake(Player *p) {
	if (!p->has_queued_actions())
		return ;
	if (teams.find(p->get_current_command().cmd_name) == teams.end()) {
		std::cerr << "Client " << std::to_string(p->get_sock_fd()) << ": Invalid teamname in handshake\n";
		Messages resp = Messages(Command::Unknown, (void *) p, (void *) &map, false);
		
		p->set_send_buffer(resp.getMessageStr());
		p->pop_command();
	}
	if (teams[p->get_current_command().cmd_name].get_conns_nbr()
			< teams[p->get_current_command().cmd_name].get_max_conns()) {
		teams[p->get_current_command().cmd_name].player2egg(p);
		p->pop_command();
	}
	p->pop_command();
}
