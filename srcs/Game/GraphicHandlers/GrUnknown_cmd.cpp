#include "Game.hpp"

std::string	Game::gr_unknown_cmd() {
	return std::string("suc\n");
}

std::string	Game::gr_unknown_cmd(Player *p) {
	(void)p;
	return gr_unknown_cmd();
}
