#pragma once

# include <string>
# include <random>

enum Command {

	/* PLAYERS COMMANDS */
	Avance,
	Droite,
	Gauche,
	Voir,
	Inventaire,
	Prend,
	Pose,
	Expulse,
	Broadcast,
	IncantationBgn,
	IncantationEnd,
	Fork,
	ConnectNbr,
	Mort,
	Unknown,

	/* GRAPHIC CLIENT COMMANDS */
	Map_size,
	Content_tile,
	Content_map,
	Team_names,
	Player_new_conn,
	Player_pos,
	Player_lvl,
	Player_inv,
	Player_expelled,
	Player_broadcast,
	Player_fork,
	Player_pose,
	Player_prend,
	Player_mort,
	Incantation_start,
	Incantation_res,
	Egg_laid_by_player,
	Egg_hatch,
	Egg_to_player,
	Egg_mort,
	Time_unit,
	Time_unit_mod,
	Game_end,
	Unknown_cmd,
	Wrong_params,
};

class Messages {
	private:
		std::string messageStr;
		
		public:
		Messages();
		Messages(Command cmd, void *player, void *map, bool success); //player: change from (void *) to (Player *)
		~Messages();
		
		std::string	&getMessageStr();
};

Command	hashString(const std::string &str, bool);
