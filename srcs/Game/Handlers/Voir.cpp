#include "Game.hpp"

void Game::_Voir(Player *p)
{
	std::string args = p->get_current_command().args;
	if (args.empty() == false) {
		this->_Unknown(p);
		return ;
	}
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
