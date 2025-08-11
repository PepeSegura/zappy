#include "Game.hpp"

std::string	Game::gr_egg_laid_by_player(int e, int n, int y, int x) {
	return std::string("enw " + std::to_string(e) + " " + std::to_string(n) + " " + std::to_string(x) + " " + std::to_string(y) + "\n");
}
