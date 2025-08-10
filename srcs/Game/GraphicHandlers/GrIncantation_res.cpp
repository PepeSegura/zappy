#include "Game.hpp"

std::string	Game::gr_incantation_res(int y, int x, int R) {
	return std::string("pie " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(R) + "\n");
}
