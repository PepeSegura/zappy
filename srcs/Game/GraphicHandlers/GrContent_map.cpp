#include "Game.hpp"

std::string	Game::gr_content_map() {
	std::string map_contents = "";
	for (int y = 0; y < map_height; ++y) {
		for (int x = 0; x < map_width; ++x) {
			map_contents += gr_content_tile(y, x);
		}
	}
	return map_contents;
}