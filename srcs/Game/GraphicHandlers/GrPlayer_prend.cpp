#include "Game.hpp"

std::string	Game::gr_player_prend_resource(int n, int i) {
	return std::string("pgt " + std::to_string(n) + " " + std::to_string(i) + "\n");
}
