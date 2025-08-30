#include "Game.hpp"

std::string	Game::gr_player_inv(int player_id)
{
	Inventory inv;
	int x, y, found = 0;

	for (auto &[team_name, team]: teams) {
		auto players = team.get_team_players();
		for (auto player: players) {
			if (player->get_id() == player_id)
			{
				found = 1;
				inv = player->get_inv();
				x = player->get_x();
				y = player->get_y();
				break ;
			}
		}
	}
	/* for (auto [fd, player] : this->playersfd_map) //buscar en los teams
	{
		if (player->get_id() == player_id)
		{
			found = 1;
			inv = player->get_inv();
			x = player->get_x();
			y = player->get_y();
			break ;
		}
	} */
	if (!found)
		return gr_wrong_params();
	return "pin " + std::to_string(player_id) + " " 
				  + std::to_string(x) + " " + std::to_string(y) + " "
				  + std::to_string(inv.get_nourriture())		+ " "
				  + std::to_string(inv.get_linemate())			+ " "
				  + std::to_string(inv.get_deraumere())			+ " "
				  + std::to_string(inv.get_sibur())				+ " "
				  + std::to_string(inv.get_mendiane())			+ " "
				  + std::to_string(inv.get_phiras())			+ " "
				  + std::to_string(inv.get_thystame())			+ "\n";
}

std::string	Game::gr_player_inv(Player *p)
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

	return gr_player_inv(player_id);
}
