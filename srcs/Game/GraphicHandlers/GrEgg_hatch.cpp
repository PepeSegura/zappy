#include "Game.hpp"

std::string	Game::gr_egg_hatch(int e) {
	(void) e;
	return std::string("msz " + std::to_string(map_width) + " " + std::to_string(map_height) + "\n");
}