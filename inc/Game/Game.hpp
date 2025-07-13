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
		std::map<int, Player *>			players_map; //key=client_fd
		std::map<std::string, Team*>	teams;

	public:
		Game();
		~Game();

		std::map<int, Player *> &get_players_map();

		void					add_player_to_map(int, Player *);
};
