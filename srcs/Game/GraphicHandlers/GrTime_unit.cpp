#include "Game.hpp"

std::string	Game::gr_time_unit() {
	return std::string("sgt " + std::to_string(time_unit) + "\n");
}