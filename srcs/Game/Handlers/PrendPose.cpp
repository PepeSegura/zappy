#include "Game.hpp"

int Game::aux_prend_pose(Player *p, std::string item, int new_tile_ammount, int new_player_ammount)
{
	std::vector<std::string> items = {
		"nourriture", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"
	};

	auto it = std::find(items.begin(), items.end(), item);
	if (it == items.end())
	{
		p->set_send_buffer("ko\n");
		return -1;
	}

	if (new_tile_ammount == -1 && this->map[p->get_y()][p->get_x()].get_inv().get_item(item) <= 0)
	{
		p->set_send_buffer("ko\n");
		return -1;
	}
	if (new_player_ammount == -1 && p->get_inv().get_item(item) <= 0)
	{
		p->set_send_buffer("ko\n");
		return -1;	
	}
	this->map[p->get_y()][p->get_x()].get_inv().add_item(item, new_tile_ammount);
	this->world_resources.add_item(item, new_tile_ammount);
	p->get_inv().add_item(item, new_player_ammount);
	p->set_send_buffer("ok\n");
	return 0;
}

void Game::_Prend(Player *p)
{
	std::cout << "EXECUTING PREND\n";

	std::string item = p->get_current_command().args;
	if (this->aux_prend_pose(p, item, -1, +1) < 0)
		return ;
	send2grclients(gr_player_prend_resource(p->get_id(), item));
	send2grclients(gr_player_inv(p->get_id()));
	send2grclients(gr_content_tile(p->get_y(), p->get_x()));
}

void Game::_Pose(Player *p)
{
	std::cout << "EXECUTING POSE\n";

	std::string item = p->get_current_command().args;
	
	if (this->aux_prend_pose(p, item, +1, -1) < 0)
		return ;
	send2grclients(gr_player_pose_resource(p->get_id(), item));
	send2grclients(gr_player_inv(p->get_id()));
	send2grclients(gr_content_tile(p->get_y(), p->get_x()));
}
