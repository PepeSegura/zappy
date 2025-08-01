#include "Game.hpp"

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
