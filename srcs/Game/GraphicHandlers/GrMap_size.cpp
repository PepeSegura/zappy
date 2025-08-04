#include "Game.hpp"

std::string	Game::gr_map_size() {
	return std::string("msz " + std::to_string(map_width) + " " + std::to_string(map_height) + "\n");
}