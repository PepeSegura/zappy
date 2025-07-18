#pragma once

# include <map>
# include <iostream>
# include <chrono>

# include "Team.hpp"
# include "Parser.hpp"
# include "Tile.hpp"

class Game;

typedef void (Game::*ActionHandler)(Player *);

class Game
{
	private:
		std::vector<std::vector<Tile>>		map;
		int									map_width, map_height;

		std::map<int, Player *>				playersfd_map; //key=client_fd
		std::map<std::string, Team>			teams;
		bool								end;
		int64_t								last_tick, tick_millis;

		std::map<Command, int64_t>			action_time_table;
		std::map<Command, ActionHandler>	handlers;
		Inventory world_resources;
		
		void init_map(Parser *);
		void init_teams(Parser *);
		void init_action_time_map();
		void init_handlers_map();

	public:
		Game();
		Game(Parser *parser);
		~Game();

		std::map<int, Player *>	&get_players_map();

		void					add_player_to_fdmap(int, Player *);
		void					add_player_to_team(std::string, Player *);
		void					remove_player(Player *);

		bool					get_end() const;

		void					run_tick();

		void					set_tick_millis(int64_t);
		void					try2handshake(Player *);

		int		get_map_width() const { return (this->map_width); };
		int		get_map_height() const { return (this->map_height); };

		/* Handlers */
		void	_Avance(Player *);
		void	_Droite(Player *p);
		void	_Gauche(Player *p);
		void	_Voir(Player *p);
		void	_Inventaire(Player *p);
		void	_Prend(Player *p);
		void	_Pose(Player *p);
		void	_Expulse(Player *p);
		void	_Broadcast(Player *p);
		void	_IncantationBgn(Player *p);
		void	_IncantationEnd(Player *p);
		void	_Fork(Player *p);
		void	_ConnectNbr(Player *p);
		void	_Mort(Player *p);
		void	_Unknown(Player *p);
};
