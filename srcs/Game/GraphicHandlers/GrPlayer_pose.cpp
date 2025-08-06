#include "Game.hpp"

std::string	Game::gr_player_pose_resource(int n, int i) {
	return std::string("pdr " + std::to_string(n) + " " + std::to_string(i) + "\n");
}
