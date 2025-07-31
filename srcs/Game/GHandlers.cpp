#include "Game.hpp"
#include <algorithm>

void Game::_Avance(Player *p)
{
	std::cout << "EXECUTING AVANCE\n";

	this->map[p->get_y()][p->get_x()].remove_player_from_team(p);
	p->Avance();
	this->map[p->get_y()][p->get_x()].add_player_to_team(p);
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
	// std::cout << "---------------------\n";
	// std::cout << "Looking at: " << p->get_dir() << std::endl;

	int actual_level = 0;
	int check_sides = 0;
	int max_level = p->get_level();
	
	std::string content_tile = "{";
	// std::cout << "-- Max level: " << max_level << std::endl;
	
	while (actual_level <= max_level)
	{
		check_sides = -actual_level;
		while (check_sides <= actual_level)
		{
			int y_coord = p->get_y();
			int x_coord = p->get_x();
			
			switch (p->get_dir())
			{
				case 'N':
					y_coord -= actual_level;
					x_coord += check_sides;
					break;
				case 'S':
					y_coord += actual_level;
					x_coord -= check_sides;
					break;
				case 'W':
					y_coord -= check_sides;
					x_coord -= actual_level;
					break;
				case 'E':
					y_coord += check_sides;
					x_coord += actual_level;
					break;
				default:
					break;
			}

			while (y_coord < 0) { y_coord += map_height; }
			while (y_coord >= map_height) { y_coord -= map_height; }
			
			while (x_coord < 0) { x_coord += map_width;	}
			while (x_coord >= map_width) { x_coord -= map_width; }
			
			// std::cout << "Inventory from: (" << x_coord << "," << y_coord << ")" << std::endl;
			// content_tile += std::to_string(tile) + " " + this->map[y_coord][x_coord].voir_tile(p) + ",";
			content_tile += this->map[y_coord][x_coord].voir_tile(p) + ",";
			
			check_sides++;
		}
		actual_level++;
	}

	if (content_tile.length() > 1)
	{
		content_tile.erase(content_tile.end() - 1);
	}
	p->set_send_buffer(content_tile + "}\n");
	// std::cout << "----------------------\n" << std::endl;
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
	this->world_resources.add_item(item, new_tile_ammount);
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
	int player_y = p->get_y(), player_x = p->get_x();
	int new_y = player_y, new_x = player_x;
	std::string comming_from;

	switch (p->get_dir())
	{
		case 'N':
			(player_y == 0) ? new_y = map_height - 1 : new_y = player_y - 1;
			comming_from = "S";
			break;
		case 'S':
			(player_y == map_height - 1) ? new_y = 0 : new_y = player_y + 1;
			comming_from = "N";
			break;
		case 'W':
			(player_x == 0) ? new_x = map_width - 1 : new_x = player_x - 1;
			comming_from = "E";
			break;
		case 'E':
			(player_x == map_width - 1) ? new_x = 0 : new_x = player_x + 1;
			comming_from = "W";
			break;
		default:
			break;
	}

	Tile& old_tile = this->map[player_y][player_x];
	Tile& new_tile = this->map[new_y][new_x];

	std::string response = "ko\n";
	for (Player* player : old_tile.get_players_list())
	{
		if (player != p)
		{
			new_tile.add_player_to_team(player);
			player->set_x(new_x);
			player->set_y(new_y);
			old_tile.remove_player_from_team(player);
			player->set_send_buffer("deplacement " + comming_from + "\n");
			response = "ok\n";
		}
	}
	p->set_send_buffer(response);
}

uint8_t Game::get_sound_direction(Player *origin, Player *dest)
{
	(void)origin, (void) dest;
	return ('1');
}

void Game::_Broadcast(Player *p)
{
	std::string msg = p->get_current_command().args;
	std::cout << "EXECUTING BROADCAST\n";
	for (auto [fd, player] : this->playersfd_map)
	{
		if (player->get_handshake() == true && player != p)
		{
			player->set_send_buffer("message 1," + msg + "\n");
		}
	}
	(void)p;
}

void Game::_IncantationBgn(Player *p)
{
	std::cout << "EXECUTING INCANTATION\n";

	std::cout << "Checking prerequisites...\n";

	std::cout << "Checking materials...\n";
	if (!check_incantation_materials(p)){
		std::cout << "error: incantation: not enough materials\n";
		p->set_send_buffer("ko\n");
		return ;
	}

	std::cout << "Checking players...\n";
	if (!check_incantation_players_bgn(p)){
		std::cout << "error: incantation: players requisite not met\n";
		p->set_send_buffer("ko\n");
		return ;
	}

	std::cout << "All preliminary checks passed!\n";

	p->IncantationBgn();
}

void Game::_IncantationEnd(Player *p)
{
	std::cout << "EXECUTING INCANTATION_END\n";
	std::cout << "Checking end requisites...\n";

	if (!p->get_encantation_precheck()) {
		std::cout << "Checking materials...\n";
		if (!check_incantation_materials(p)){
			std::cout << "error: incantation: not enough materials\n";
			p->set_send_buffer("ko\n");
			return ;
		}
	
		std::cout << "Checking players...\n";
		if (!check_incantation_players_end(p)) {
	
			std::cout << "error: incantation: players requisite not met\n";
			p->set_send_buffer("ko\n");
			return ;
		}
		remove_incantation_materials(p);
		mark_all_enchanting_players(p);
	} else {
		std::cout << "Checks already done by another player\n";
		p->set_encantation_precheck(false);
	}

	std::cout << "All checks passed! Level up!\n";
	p->IncantationEnd();
}

void Game::_Fork(Player *p)
{
	std::cout << "EXECUTING FORK\n";

	Player *egg = new Player(p->get_team_name());

	egg->set_x(p->get_x());
	egg->set_y(p->get_y());

	this->teams[p->get_team_name()].inc_max_conns();
	this->teams[p->get_team_name()].add_player(egg);
	this->map[p->get_y()][p->get_x()].add_player_to_team(egg);

	p->set_send_buffer("ok\n");
}

void Game::_ConnectNbr(Player *p)
{
	std::cout << "EXECUTING CONNECT_NBR\n";

	uint32_t conn_nbr = this->teams[p->get_team_name()].get_avail_conns();
	p->set_send_buffer(std::to_string(conn_nbr) + "\n");
}

void Game::_Mort(Player *p)
{
	std::cout << "EXECUTING MORT\n";

	p->set_send_buffer("mort\n");
}

void Game::_Unknown(Player *p)
{
	std::cout << "IGNORING UNKNOWN COMMAND\n";

	p->set_send_buffer("ko\n");
}

bool Game::check_incantation_materials(Player *p) {
	Inventory &inv = map[p->get_y()][p->get_x()].get_inv();
	if (inv.get_linemate() < incantation_lvl_reqs[p->get_level()].linemate_req) {
		std::cout << "error: incantation: not enough linemate\n";
		return false;
	}
	if (inv.get_deraumere() < incantation_lvl_reqs[p->get_level()].deraumere_req) {
		std::cout << "error: incantation: not enough deraumere\n";
		return false;
	}
	if (inv.get_sibur() < incantation_lvl_reqs[p->get_level()].sibur_req) {
		std::cout << "error: incantation: not enough sibur\n";
		return false;
	}
	if (inv.get_mendiane() < incantation_lvl_reqs[p->get_level()].mendiane_req) {
		std::cout << "error: incantation: not enough mendiane\n";
		return false;
	}
	if (inv.get_phiras() < incantation_lvl_reqs[p->get_level()].phiras_req) {
		std::cout << "error: incantation: not enough phiras\n";
		return false;
	}
	if (inv.get_thystame() < incantation_lvl_reqs[p->get_level()].thystame_req) {
		std::cout << "error: incantation: not enough thystame\n";
		return false;
	}
	return true;
}

bool Game::check_incantation_players_bgn(Player *p) {
	if (map[p->get_y()][p->get_x()].players_at_level(p->get_level()) < incantation_lvl_reqs[p->get_level()].nbr_of_players)
		return false;
	return true;
}

bool Game::check_incantation_players_end(Player *p) {
	if (map[p->get_y()][p->get_x()].players_at_level_and_enchating(p->get_level()) < incantation_lvl_reqs[p->get_level()].nbr_of_players)
		return false;
	return true;
}

void Game::remove_incantation_materials(Player *p) {
	Inventory &inv = map[p->get_y()][p->get_x()].get_inv();

	if (incantation_lvl_reqs[p->get_level()].linemate_req) {
		inv.add_linemate(-incantation_lvl_reqs[p->get_level()].linemate_req);
	}
	if (incantation_lvl_reqs[p->get_level()].deraumere_req) {
		inv.add_deraumere(-incantation_lvl_reqs[p->get_level()].deraumere_req);
	}
	if (incantation_lvl_reqs[p->get_level()].sibur_req) {
		inv.add_sibur(-incantation_lvl_reqs[p->get_level()].sibur_req);
	}
	if (incantation_lvl_reqs[p->get_level()].mendiane_req) {
		inv.add_mendiane(-incantation_lvl_reqs[p->get_level()].mendiane_req);
	}
	if (incantation_lvl_reqs[p->get_level()].phiras_req) {
		inv.add_phiras(-incantation_lvl_reqs[p->get_level()].phiras_req);
	}
	if (incantation_lvl_reqs[p->get_level()].thystame_req) {
		inv.add_thystame(-incantation_lvl_reqs[p->get_level()].thystame_req);
	}
}

void Game::mark_all_enchanting_players(Player *p) {
	std::vector<Player *> players = map[p->get_y()][p->get_x()].get_players_list();

	for (auto other_p : players) {
		if (p != other_p && other_p->get_is_encantating() && p->get_level() == other_p->get_level())
			other_p->set_encantation_precheck(true);
	}
}
