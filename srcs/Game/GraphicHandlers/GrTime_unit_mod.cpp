#include "Game.hpp"

std::string	Game::gr_time_unit_mod(int t) {
	set_tick_millis(t);
	return std::string("sgt " + std::to_string(time_unit) + "\n");
}

std::string	Game::gr_time_unit_mod(Player *p)
{
	std::string args = p->get_current_command().args;
	std::vector<std::string> splitted_args = Utils::split_by_spaces(args);

	int time_unit = -1;
	try
	{
		if (splitted_args.size() != 1)
			throw std::runtime_error("Only 1 time unit pls");

		time_unit = std::stoi(splitted_args[0]);
		if (time_unit < 1 || time_unit > 1000)
			throw std::runtime_error("Invalid time unit: " + std::to_string(time_unit));
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
		return gr_wrong_params();
	}

	return gr_time_unit_mod(time_unit);
}
