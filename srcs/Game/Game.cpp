#include "Game.hpp"
#include "Utils.hpp"
#include <iomanip>

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

void Game::add_player_to_fdmap(int fd, Player *player) {
	playersfd_map.insert_or_assign(fd, player);
}

void Game::gen_item(int (Inventory::*getter)() const, void (Inventory::*adder)(int), Item item)
{
	const int item_max_count = item_densities.at(item) * this->map_height * this->map_width;

	while (1)
	{
		if ((this->world_resources.*getter)() >= item_max_count)
			return ;
	
		int random_height = Utils::random_between(0, this->map_height - 1);
		int random_width = Utils::random_between(0, this->map_width - 1);
	
		Inventory& random_tile = this->map[random_height][random_width].get_inv();
	
		(random_tile.*adder)(1);
		(world_resources.*adder)(1);

		/* std::cout << "(" << random_height << ", " << random_width << ") -> "
				  << item_string.at(item)
				  << std::endl; */
	}
}

void Game::gen_map_resources()
{
	//std::cout << "Generating new resources" << std::endl;

	gen_item(&Inventory::get_nourriture, &Inventory::add_nourriture, Item::NOURRITURE);
    gen_item(&Inventory::get_linemate, &Inventory::add_linemate, Item::LINEMATE);
    gen_item(&Inventory::get_deraumere, &Inventory::add_deraumere, Item::DERAUMERE);
    gen_item(&Inventory::get_sibur, &Inventory::add_sibur, Item::SIBUR);
    gen_item(&Inventory::get_mendiane, &Inventory::add_mendiane, Item::MENDIANE);
    gen_item(&Inventory::get_phiras, &Inventory::add_phiras, Item::PHIRAS);
    gen_item(&Inventory::get_thystame, &Inventory::add_thystame, Item::THYSTAME);

	//std::cout << "---\nTotal World resources:\n" << this->world_resources;
}

void Game::init_map(Parser *parser)
{
	int width  = parser->getWidth();
	int height = parser->getHeight();

	this->map.reserve(height);
	for (int i = 0; i < height; ++i)
		this->map.emplace_back(width);
		
	this->map_width = width;
	this->map_height = height;
	gen_map_resources();
}

void Game::init_teams(Parser *parser)
{
	t_teams_names teamNames = parser->getTeamsNames();

	for (const auto& name : teamNames) {
		this->teams[name] = Team(name, parser->getTeamsMembersLimit(), this);
		this->teams[name].init_eggs(parser->getWidth(), parser->getHeight());
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
	action_time_table[IncantationBgn] = 0;
	action_time_table[IncantationEnd] = 300;
	action_time_table[Fork] = 42;
	action_time_table[ConnectNbr] = 0;
	action_time_table[Mort] = 0;
	action_time_table[Unknown] = 0;
}

void Game::init_encantation_reqs_map()
{
	Incantation_Reqs tmp;
	tmp.nbr_of_players = 1;
	tmp.linemate_req = 1;
	tmp.deraumere_req = 0;
	tmp.sibur_req = 0;
	tmp.mendiane_req = 0;
	tmp.phiras_req = 0;
	tmp.thystame_req = 0;
	incantation_lvl_reqs[1] = tmp;
	tmp.nbr_of_players = 2;
	tmp.linemate_req = 1;
	tmp.deraumere_req = 1;
	tmp.sibur_req = 1;
	tmp.mendiane_req = 0;
	tmp.phiras_req = 0;
	tmp.thystame_req = 0;
	incantation_lvl_reqs[2] = tmp;
	tmp.nbr_of_players = 2;
	tmp.linemate_req = 2;
	tmp.deraumere_req = 0;
	tmp.sibur_req = 1;
	tmp.mendiane_req = 0;
	tmp.phiras_req = 2;
	tmp.thystame_req = 0;
	incantation_lvl_reqs[3] = tmp;
	tmp.nbr_of_players = 4;
	tmp.linemate_req = 1;
	tmp.deraumere_req = 1;
	tmp.sibur_req = 2;
	tmp.mendiane_req = 0;
	tmp.phiras_req = 1;
	tmp.thystame_req = 0;
	incantation_lvl_reqs[4] = tmp;
	tmp.nbr_of_players = 4;
	tmp.linemate_req = 1;
	tmp.deraumere_req = 2;
	tmp.sibur_req = 1;
	tmp.mendiane_req = 3;
	tmp.phiras_req = 0;
	tmp.thystame_req = 0;
	incantation_lvl_reqs[5] = tmp;
	tmp.nbr_of_players = 6;
	tmp.linemate_req = 1;
	tmp.deraumere_req = 2;
	tmp.sibur_req = 3;
	tmp.mendiane_req = 0;
	tmp.phiras_req = 1;
	tmp.thystame_req = 0;
	incantation_lvl_reqs[6] = tmp;
	tmp.nbr_of_players = 6;
	tmp.linemate_req = 2;
	tmp.deraumere_req = 2;
	tmp.sibur_req = 2;
	tmp.mendiane_req = 2;
	tmp.phiras_req = 2;
	tmp.thystame_req = 1;
	incantation_lvl_reqs[7] = tmp;
	std::cout << "Reqs lvl n:pl;li;de;si;me;ph;th\n";
	for (auto [i, reqs] : incantation_lvl_reqs) {
		std::cout << "Reqs lvl " << std::to_string(i) << ": " 
		<< std::to_string(reqs.nbr_of_players) << "; " 
		<< std::to_string(reqs.linemate_req) << "; " 
		<< std::to_string(reqs.deraumere_req) << "; " 
		<< std::to_string(reqs.sibur_req) << "; " 
		<< std::to_string(reqs.mendiane_req) << "; " 
		<< std::to_string(reqs.phiras_req) << "; " 
		<< std::to_string(reqs.thystame_req) << std::endl;
	}
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
	init_encantation_reqs_map();
	
	this->end = false;
	this->debug = parser->getDebug();
	set_tick_millis(parser->getTimeFreq());
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

	if (graphicfd_map.find(p->get_sock_fd()) != graphicfd_map.end())
	{
		graphicfd_map.erase(p->get_sock_fd());
		delete p;
		return;
	}
	//remove player from tile
	
	/* for (auto& [name, team] : teams)
		team.remove_player(p); */
	
	if (!p->get_handshake() || p->get_dead()) { //delete players that havent completed handshake (incomplate players) and dead players
		for (auto& [name, team] : teams)
			team.remove_player(p);
		//remove from tile
		map[p->get_y()][p->get_x()].remove_player_from_team(p);
		delete p;
	} else {
		teams[p->get_team_name()].dec_conns_nbr();
		p->set_sock_fd(-1);
		p->set_disconnect(true); //set full players as disconnected to allow reconnect
	}
}

bool Game::get_end() const {
	return this->end;
}

void Game::run_tick() {
	static uint8_t ticks_count = 0;

	now = std::chrono::high_resolution_clock::now();
    auto elapsed = now - last_tick;
	if (elapsed >= tick_interval) { //enough time has passed, run tick logic
    	if (++ticks_count == FOOD_SPAWN_RATE) { ticks_count = 0, gen_map_resources(); } 
		for (auto &[key, team] : teams) {
			auto players = team.get_team_players();
			for (auto player : players) {
				if (player->get_handshake()) {
					player->check_food_and_eat();
				}
				if (player->get_dead()) {
					player->set_send_buffer("mort\n");
					if (player->get_disconnected()) { remove_player(player); }
					continue;
				}
				if (player->get_state() == Player_States::Free) {
					try2start_action(player);
				}
				if (player->get_state() == Player_States::ExecutingAction) {
					check_player_action(player);
					continue; 
				}
			}
		}
		for (auto& [fd, player] : playersfd_map) { // for each connected player
			if (player->get_state() == Player_States::Handshake) { // if its still in handshake state
				try2handshake(player);
			}
		}
		last_tick = now; // update last_tick timestamp
	}
}

void	Game::set_tick_millis(int64_t t) {
	if (t < 1 || t > 1000) {
		std::cerr << "Invalid freq; allowed values [1, 1000]\n";
		return ;
	}
	this->tick_interval = std::chrono::nanoseconds(1000000000 / t);
}

void	Game::try2handshake(Player *p) {
	if (!p->has_queued_actions())
		return ;
	if (p->get_current_command().cmd_name == GRAPHIC_NAME) {
		p->set_graphic_client(true);
		p->set_handshake(true);
		p->set_state(Player_States::Free);
		p->pop_command();
		std::cout << "NEW GCLIENT WITH FD:" << p->get_sock_fd() << std::endl;
		graphicfd_map[p->get_sock_fd()] = p;
		return ;
	}
	if (teams.find(p->get_current_command().cmd_name) == teams.end()) {
		std::cerr << "Client " << std::to_string(p->get_sock_fd()) << ": Invalid teamname in handshake\n";
		Messages resp = Messages(Command::Unknown, (void *) p, (void *) &map, false);
		
		p->set_send_buffer(resp.getMessageStr());
		p->pop_command();
		p->set_dead(true); //kick players that provide invalid team names
		return ;
	}
	if (teams[p->get_current_command().cmd_name].get_avail_conns() > 0) {
		Player *connected_player = teams[p->get_current_command().cmd_name].player2egg(p);
		playersfd_map[connected_player->get_sock_fd()] = connected_player;
		
		std::string response = std::to_string(teams[p->get_current_command().cmd_name].get_avail_conns())
			+ "\n" + std::to_string(this->map_width) + " " + std::to_string(this->map_height) + "\n";
		delete p;
		connected_player->set_send_buffer(response);
		return ;
	}
	std::string response = std::to_string(teams[p->get_current_command().cmd_name].get_avail_conns()) + "\n";
	p->set_send_buffer(response);
	p->pop_command();
	//p->set_dead(true); //kick players that try to connect to teams without free spaces
}

void	Game::check_player_action(Player *player) {
	auto action_time = action_time_table[player->get_current_command().cmd] * get_tick_interval();
	if (action_time <= now - player->get_last_start_time()) { //action ended, call handlers
		(this->*handlers[player->get_current_command().cmd])(player);
		player->pop_command();
		player->set_state(Player_States::Free);
		try2start_action(player);
	}
}

void Game::try2start_action(Player *player) {
	if (player->has_queued_actions()) {
		player->set_last_start_time(now);
		player->set_state(Player_States::ExecutingAction);
	}
}
