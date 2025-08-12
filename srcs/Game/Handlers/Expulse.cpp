#include "Game.hpp"

void Game::_Expulse(Player *p)
{
	std::string args = p->get_current_command().args;
	if (args.empty() == false) {
		this->_Unknown(p);
		return ;
	}
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
			send2grclients(gr_player_expelled(player->get_id()));
			send2grclients(gr_player_pos(player->get_id()));
		}
	}
	p->set_send_buffer(response);
	
}
