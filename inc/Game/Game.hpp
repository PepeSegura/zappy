#pragma once

# include <map>
# include <iostream>
# include "Team.hpp"

class Tile {
	private:
		Inventory				inv;
		std::vector<Player*>	players;

	public:
		Tile(){};
		~Tile(){};
		Tile& operator=(const Tile& other);
};

class Game
{
	private:
		std::vector<std::vector<Tile>>	map;
		std::map<std::string, Team*>	teams;

	public:
		Game();
		~Game();
};
