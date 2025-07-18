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
		void	_Avance(Player*);
		void	_Droite(Player*);
		void	_Gauche(Player*);
		void	_Voir(Player*);
		void	_Inventaire(Player*);
		void	aux_prend_pose(Player*, std::string, int, int);
		void	_Prend(Player*);
		void	_Pose(Player*);
		void	_Expulse(Player*);
		void	_Broadcast(Player*);
		void	_IncantationBgn(Player*);
		void	_IncantationEnd(Player*);
		void	_Fork(Player*);
		void	_ConnectNbr(Player*);
		void	_Mort(Player*);
		void	_Unknown(Player*);
};
