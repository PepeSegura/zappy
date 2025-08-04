#include "Game.hpp"

std::string	Game::gr_team_names() {
	std::string team_names = "";
	for (auto &[key, team] : teams)
		team_names += ("tna " + key + "\n");
	return team_names;
}

std::string	Game::gr_team_names(Player *p) {
	(void)p;
	return gr_team_names();
}
