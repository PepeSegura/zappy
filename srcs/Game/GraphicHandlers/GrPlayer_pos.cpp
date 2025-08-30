#include "Game.hpp"

std::string	Game::gr_player_pos(int player_id)
{
	char dir;
	int x, y, found = 0;

	for (auto &[team_name, team]: teams) {
		auto players = team.get_team_players();
		for (auto player: players) {
			if (player->get_id() == player_id) {
				found = 1;
				dir = (char)player->get_dir();
				x = player->get_x();
				y = player->get_y();
				break ;
			}
		}
	}
	if (!found)
		return gr_wrong_params();

	switch (dir) {
		case 'N':
			found = 1;
			break ;
		case 'S':
			found = 3;
			break ;
		case 'E':
			found = 2;
			break ;
		case 'W':
			found = 4;
			break ;
		default:
			found = 1;
			break ;
	}
	return "ppo " + std::to_string(player_id) + " " 
				  + std::to_string(x) + " " + std::to_string(y) + " "
				  + std::to_string(found)		+ "\n";
}

std::string	Game::gr_player_pos(Player *p)
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

	return gr_player_pos(player_id);
}
