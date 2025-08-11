#include "Game.hpp"

std::string	Game::gr_player_new_conn(Player *player)
{
	char dir;
	int x, y, id, level;
	std::string team_name;

	dir = (char)player->get_dir();
	x = player->get_x();
	y = player->get_y();
	id = player->get_id();
	level = player->get_level();
	team_name = player->get_team_name();


	switch (dir) {
		case 'N':
			dir = 1;
			break ;
		case 'S':
			dir = 3;
			break ;
		case 'E':
			dir = 2;
			break ;
		case 'W':
			dir = 4;
			break ;
		default:
			dir = 1;
			break ;
	}
	return "pnw " + std::to_string(id) + " "
				  + std::to_string(x) + " " + std::to_string(y) + " "
				  + std::to_string(dir) + " " + std::to_string(level) + " "
				  + team_name + "\n";
}