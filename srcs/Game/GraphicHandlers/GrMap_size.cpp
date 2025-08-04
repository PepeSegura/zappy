#include "Game.hpp"

std::string	Game::gr_map_size() {
	return std::string("msz " + std::to_string(map_width) + " " + std::to_string(map_height) + "\n");
}

std::string	Game::gr_map_size(Player *p) {
	(void)p;
	return gr_map_size();
}
