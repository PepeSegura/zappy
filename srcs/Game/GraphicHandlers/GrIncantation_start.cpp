#include "Game.hpp"

std::string	Game::gr_incantation_start(int y, int x, int L, std::string ids) {
	std::string str("pic " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(L) + " " + ids + "\n");
	return (str);
}
