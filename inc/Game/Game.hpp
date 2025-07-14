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
		std::map<int, Player *>			playersfd_map; //key=client_fd
		std::map<std::string, Team>		teams;


		Inventory world_resources;
		
		void init_map(Parser *);
		void init_teams(Parser *);

	public:
		Game();
		Game(Parser *parser);
		~Game();

		std::map<int, Player *>	&get_players_map();

		void					add_player_to_fdmap(int, Player *);
		void					add_player_to_team(std::string, Player *);
		void					remove_player(Player *);
};
