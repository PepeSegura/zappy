#include "Game.hpp"
#include <algorithm>

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
	this->map_width = width;
	this->map_height = height;
}

void Game::init_teams(Parser *parser)
{
	t_teams_names teamNames = parser->getTeamsNames();

	for (const auto& name : teamNames) {
		this->teams[name] = Team(name, parser->getTeamsMembersLimit());
		this->teams[name].init_eggs(parser->getHeight(), parser->getWidth());
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

void Game::_Avance(Player *p)
{
	std::cout << "EXECUTING AVANCE\n";
	this->map[p->get_x()][p->get_y()].remove_player_from_team(p);
	p->Avance();
	this->map[p->get_x()][p->get_y()].add_player_to_team(p);
	Messages rsp = Messages(Command::Avance, (void *) p, (void *) &map, true);
	p->set_send_buffer(rsp.getMessageStr());
}

void Game::_Droite(Player *p)
{
	std::cout << "EXECUTING DROITE\n";
	p->Droite();
	Messages rsp = Messages(Command::Droite, (void *) p, (void *) &map, true);
	p->set_send_buffer(rsp.getMessageStr());
}

void Game::_Gauche(Player *p)
{
	std::cout << "EXECUTING GAUCHE\n";
	p->Gauche();
	Messages rsp = Messages(Command::Gauche, (void *) p, (void *) &map, true);
	p->set_send_buffer(rsp.getMessageStr());
}

void Game::_Voir(Player *p)
{
	std::cout << "EXECUTING VOIR\n";
	(void)p;
}

void Game::_Inventaire(Player *p)
{
	std::cout << "EXECUTING INVENTAIRE\n";
	std::cout << "Inventory: " << p->Inventaire() << std::endl;
	p->set_send_buffer(p->Inventaire());
}

void Game::aux_prend_pose(Player *p, std::string item, int new_tile_ammount, int new_player_ammount)
{
	std::vector<std::string> items = {
		"nourriture", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"
	};

	auto it = std::find(items.begin(), items.end(), item);
	if (it == items.end())
	{
		p->set_send_buffer("ko\n");
		return ;
	}

	if (new_tile_ammount == -1 && this->map[p->get_y()][p->get_x()].get_inv().get_item(item) <= 0)
	{
		p->set_send_buffer("ko\n");
		return ;
	}
	if (new_player_ammount == -1 && p->get_inv().get_item(item) <= 0)
	{
		p->set_send_buffer("ko\n");
		return ;	
	}
	this->map[p->get_y()][p->get_x()].get_inv().add_item(item, new_tile_ammount);
	p->get_inv().add_item(item, new_player_ammount);
	p->set_send_buffer("ok\n");
}

void Game::_Prend(Player *p)
{
	std::cout << "EXECUTING PREND\n";
	std::string item = p->get_current_command().args;
	this->aux_prend_pose(p, item, -1, +1);
}

void Game::_Pose(Player *p)
{
	std::cout << "EXECUTING POSE\n";
	std::string item = p->get_current_command().args;
	this->aux_prend_pose(p, item, +1, -1);
}

void Game::_Expulse(Player *p)
{
	std::cout << "EXECUTING EXPULSE\n";
	(void)p;
}

void Game::_Broadcast(Player *p)
{
	std::cout << "EXECUTING BROADCAST\n";
	(void)p;
}

void Game::_IncantationBgn(Player *p)
{
	std::cout << "EXECUTING INCANTATION\n";
	(void)p;
}

void Game::_IncantationEnd(Player *p)
{
	std::cout << "EXECUTING INCANTATION_END\n";
	(void)p;
}

void Game::_Fork(Player *p)
{
	std::cout << "EXECUTING FORK\n";
	(void)p;
}

void Game::_ConnectNbr(Player *p)
{
	std::cout << "EXECUTING CONNECT_NBR\n";
	(void)p;
}

void Game::_Mort(Player *p)
{
	std::cout << "EXECUTING MORT\n";
	(void)p;
}

void Game::_Unknown(Player *p)
{
	std::cout << "IGNORING UNKNOWN COMMAND\n";
	Messages rsp = Messages(Command::Unknown, (void *) p, (void *) &map, true);
	p->set_send_buffer(rsp.getMessageStr());
}


void Game::init_handlers_map()
{
	handlers[Avance] = &Game::_Avance;
	handlers[Droite] = &Game::_Droite;
	handlers[Gauche] = &Game::_Gauche;
	handlers[Voir] = &Game::_Voir;
	handlers[Inventaire] = &Game::_Inventaire;
	handlers[Prend] = &Game::_Prend;
	handlers[Pose] = &Game::_Pose;
	handlers[Expulse] = &Game::_Expulse;
	handlers[Broadcast] = &Game::_Broadcast;
	handlers[IncantationBgn] = &Game::_IncantationBgn;
	handlers[IncantationEnd] = &Game::_IncantationEnd;
	handlers[Fork] = &Game::_Fork;
	handlers[ConnectNbr] = &Game::_ConnectNbr;
	handlers[Mort] = &Game::_Mort;
	handlers[Unknown] = &Game::_Unknown;
}


Game::Game(Parser *parser)
{
	init_map(parser);
	init_teams(parser);
	init_action_time_map();
	init_handlers_map();
	
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
	
	/* for (auto& [name, team] : teams)
		team.remove_player(p); */
	
	if (!p->get_handshake())
		delete p; //delete players that havent completed handshake (incomplate players)
	else {
		teams[p->get_team_name()].dec_conns();
		p->set_disconnect(true); //set full players as disconnected to allow reconnect
	}
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
					(this->*handlers[player->get_current_command().cmd])(player);
					player->pop_command();
					player->set_state(Player_States::Free);
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
		return ;
	}
	if (teams[p->get_current_command().cmd_name].get_avail_conns() > 0) {
		Player *connected_player = teams[p->get_current_command().cmd_name].player2egg(p);
		playersfd_map[connected_player->get_sock_fd()] = connected_player;
		
		std::string response = std::to_string(teams[p->get_current_command().cmd_name].get_avail_conns())
			+ "\n" + std::to_string(connected_player->get_x()) + " " + std::to_string(connected_player->get_y()) + "\n";
		delete p;
		connected_player->set_send_buffer(response);
		return ;
	}
	std::string response = std::to_string(teams[p->get_current_command().cmd_name].get_avail_conns()) + "\n";
	p->set_send_buffer(response);
	p->pop_command();
}
