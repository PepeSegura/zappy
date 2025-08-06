#include "Game.hpp"

std::string	Game::gr_player_lvl(int player_id)
{
	int lvl, found = 0;

	for (auto [fd, player] : this->playersfd_map)
	{
		if (player->get_id() == player_id)
		{
			found = 1;
			lvl = player->get_level();
			break ;
		}
	}
	if (!found)
		return gr_wrong_params();
	return "plv " + std::to_string(player_id) + " "
				  + std::to_string(lvl)			+ "\n";
}

std::string	Game::gr_player_lvl(Player *p)
{
	std::string args = p->get_current_command().args;
	std::vector<std::string> splitted_args = Utils::split_by_spaces(args);

	int player_id = -1;
	try
	{
		if (splitted_args.size() != 1)
			throw std::runtime_error("Only 1 id pls");

		player_id = std::stoi(splitted_args[0]);
		if (player_id < 0)
			throw std::runtime_error("Only positive ids");
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
		return gr_wrong_params();
	}

	return gr_player_lvl(player_id);
}
