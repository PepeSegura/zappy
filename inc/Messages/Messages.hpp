#pragma once

# include <string>
# include <random>


enum Command {
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
	Unknown
};

class Messages {
	private:
		std::string messageStr;
		Command	hashString(const std::string &str) const;

	public:
		Messages();
		Messages(const std::string &cmd, void *player, void *map, bool success); //player: change from (void *) to (Player *)
		~Messages();

		std::string	getMessageStr() const;
};
