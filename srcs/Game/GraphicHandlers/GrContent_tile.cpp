#include "Game.hpp"

std::string	Game::gr_content_tile(int y, int x) {
	Inventory &tile_inv = map[y][x].get_inv();
	return std::string("bct " + std::to_string(x) + " " + std::to_string(y) + " "
		+ std::to_string(tile_inv.get_nourriture()) + " " + std::to_string(tile_inv.get_linemate()) + " "
		+ std::to_string(tile_inv.get_deraumere()) + " " + std::to_string(tile_inv.get_sibur()) + " "
		+ std::to_string(tile_inv.get_mendiane()) + " " + std::to_string(tile_inv.get_phiras()) + " "
		+ std::to_string(tile_inv.get_thystame()) + "\n");
}

std::string	gr_content_tile(Player *p) {
	std::string args = p->get_current_command().args;

	// args.sp
}
