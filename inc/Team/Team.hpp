#pragma once

# include <vector>
# include <algorithm>
# include "Player.hpp"

class Team
{
	private:
		std::vector<Player*> players;

	public:
		Team();
		~Team();

		void	addPlayer(Player* player);
		void	removePlayer(Player* player);

};


