#include "Game.hpp"

std::string	Game::gr_player_broadcast(int n, std::string msg) {
	return std::string("pbc " + std::to_string(n) + " " + msg + "\n");
}
