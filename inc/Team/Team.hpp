#pragma once

# include <vector>
# include <algorithm>
# include "Player.hpp"

class Team
{
	private:
		std::string name;
		std::vector<Player*> players;

	public:
		Team();
		Team(std::string _name);
		~Team();

		std::string	get_name() const;
		void		add_player(Player* player);
		void		remove_player(Player* player);
};


