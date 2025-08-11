#include "Game.hpp"

std::string	Game::gr_player_prend_resource(int n, std::string item) {
	int itemhash = Utils::hash_item(item);
	return std::string("pgt " + std::to_string(n) + " " + std::to_string(itemhash) + "\n");
}
