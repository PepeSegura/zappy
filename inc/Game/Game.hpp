#pragma once

# include <map>
# include <iostream>
# include "Team.hpp"
# include "Parser.hpp"
# include "Tile.hpp"

class Game
{
	private:
		std::vector<std::vector<Tile>>	map;
		std::map<std::string, Team>		teams;
		
		void init_map(Parser *);
		void init_teams(Parser *);

	public:
		Game();
		Game(Parser *parser);
		~Game();

		void add_player(std::string, Player *);
		void remove_player(Player *);
};
