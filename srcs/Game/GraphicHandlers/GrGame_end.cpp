#include "Game.hpp"

std::string	Game::gr_game_end() {
	return std::string("seg " + winner_team + "\n");
}