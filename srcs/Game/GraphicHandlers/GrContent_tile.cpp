#include "Game.hpp"

std::string	Game::gr_content_tile(int y, int x) {
	Inventory &tile_inv = map[y][x].get_inv();
	return std::string("bct " + std::to_string(x) + " " + std::to_string(y) + " "
		+ std::to_string(tile_inv.get_nourriture()) + " " + std::to_string(tile_inv.get_linemate()) + " "
		+ std::to_string(tile_inv.get_deraumere()) + " " + std::to_string(tile_inv.get_sibur()) + " "
		+ std::to_string(tile_inv.get_mendiane()) + " " + std::to_string(tile_inv.get_phiras()) + " "
		+ std::to_string(tile_inv.get_thystame()) + "\n");
}

std::string	Game::gr_content_tile(Player *p) {
	std::string args = p->get_current_command().args;
	std::vector<std::string> splitted_args = Utils::split_by_spaces(args);

	int x = -1, y = -1;
	try
	{
		if (splitted_args.size() != 2)
			throw std::runtime_error("Incorrect number of coordinates");

		x = std::stoi(splitted_args[0]);
		y = std::stoi(splitted_args[1]);
		if (x < 0 || y < 0 || x >= this->map_width || y >= this->map_height)
			throw std::runtime_error("Invalid coordinates");
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
		return gr_wrong_params();
	}

	return gr_content_tile(y, x);
}
