#include "Game.hpp"

std::string	Game::gr_server_msg(std::string M) {
	std::string team_names = "";
	for (auto &[key, team] : teams)
		team_names += ("tna " + key + "\n");
	return team_names;
}