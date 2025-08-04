#include "Game.hpp"

std::string	Game::gr_time_unit_mod(Player *p) {
	(void) p; // TODO: extract time unit from graphic client (p) command queue, convert to int and check corner cases
	set_tick_millis(69);
	return std::string("sgt " + std::to_string(time_unit) + "\n");
}