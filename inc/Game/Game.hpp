#pragma once

# include <map>
# include <iostream>
# include <chrono>

# include "Utils.hpp"
# include "Team.hpp"
# include "Parser.hpp"
# include "Tile.hpp"

class Game;

typedef void (Game::*ActionHandler)(Player *);
typedef std::vector<std::vector<Tile>> Tile_Map;

struct Incantation_Reqs {
	int		nbr_of_players, linemate_req,
			deraumere_req, sibur_req,
			mendiane_req, phiras_req,
			thystame_req;
};

# define FOOD_SPAWN_RATE 20

class Game
{
	private:
		Tile_Map							map;
		int									map_width, map_height;

		std::map<int, Player *>				playersfd_map; //key=client_fd
		std::map<std::string, Team>			teams;
		bool								end;

		std::chrono::nanoseconds						tick_interval;
		std::chrono::high_resolution_clock::time_point	last_tick, now;

		std::map<Command, int64_t>			action_time_table;
		std::map<int, Incantation_Reqs>		incantation_lvl_reqs;
		std::map<Command, ActionHandler>	handlers;
		Inventory world_resources;
		
		void init_map(Parser *);
		void init_teams(Parser *);
		void init_action_time_map();
		void init_encantation_reqs_map();
		void init_handlers_map();
		void check_player_action(Player *);
		void try2start_action(Player *);

		bool	check_incantation_materials(Player *);
		bool	check_incantation_players_bgn(Player *);
		bool	check_incantation_players_end(Player *);
		void	remove_incantation_materials(Player *);
		void	mark_all_enchanting_players(Player *);

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

		void					gen_item(int (Inventory::*getter)() const, void (Inventory::*adder)(int), Item);
		void					gen_map_resources();

		void					set_tick_millis(int64_t);
		void					try2handshake(Player *);

		int		get_map_width() const { return (this->map_width); };
		int		get_map_height() const { return (this->map_height); };
		std::chrono::nanoseconds	get_tick_interval() const { return (this->tick_interval); };

		Tile_Map	&get_tile_map() { return map; }

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

		std::pair<int, int>	dda(Player *origin, Player *dest, int y, int x);
		double	dist_copy_pos(Player *origin, Player *dest, int y, int x);
		uint8_t	get_sound_direction(Player *origin, Player *dest);
		void	_Broadcast(Player*);
		void	_IncantationBgn(Player*);
		void	_IncantationEnd(Player*);
		void	_Fork(Player*);
		void	_ConnectNbr(Player*);
		void	_Mort(Player*);
		void	_Unknown(Player*);
};
