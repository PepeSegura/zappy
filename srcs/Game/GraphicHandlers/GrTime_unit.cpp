#include "Game.hpp"

std::string	Game::gr_time_unit() {
	return std::string("sgt " + std::to_string(time_unit) + "\n");
}

std::string	Game::gr_time_unit(Player *p) {
	(void)p;
	return gr_time_unit();
}
