#include "Messages.hpp"

Messages::Messages() {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist2048(0,2047);
	switch (dist2048(rng) % 15) {
		case Avance:
		case Droite:
		case Gauche:
		case Broadcast:
		case Fork:
			messageStr = "ok\n";
			break;
		case Voir:
			//voir logic with map content in player pos
			messageStr = "{phiras, phiras sibur sibur, nourriture sibur}\n";
			break;
		case Inventaire:
			//inventary logic from players inv
			messageStr = "{nourriture 0, linemate 0, deraumere 10, sibur 2, mendiane 0, phiras 0, thystame 0}\n";
			break;
		case Prend:
		case Pose:
		case Expulse:
			if (dist2048(rng) % 2){
				messageStr = "ok\n";
				break;
			}
			messageStr = "ko\n";
			break;
		case IncantationBgn:
			messageStr = "elevation en cours\n";
			break;
		case IncantationEnd:
			messageStr = "niveau actuel : " + std::to_string(((dist2048(rng) % 8) + 1)) + "\n"; //todo take level from player
			break;
		case ConnectNbr:
			messageStr = std::to_string(dist2048(rng) % 6) + "\n";
			break;
		case Mort:
			messageStr = "mort\n";
			break;
		case Unknown:
			messageStr = "unknown\n";
			break;
	}
}

Messages::Messages(Command cmd, void *player, void *map, bool success) {
	(void) player;
	(void) map;
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist2048(0,2047);
	switch (cmd) {
		case Avance:
		case Droite:
		case Gauche:
		case Broadcast:
		case Fork:
			messageStr = "ok\n";
			break;
		case Voir:
			//voir logic with map content in player pos
			messageStr = "{phiras, phiras sibur sibur, nourriture sibur}\n";
			break;
		case Inventaire:
			//inventary logic from players inv
			messageStr = "{phiras 3, sibur 2}\n";
			break;
		case Prend:
		case Pose:
		case Expulse:
			if (success){
				messageStr = "ok\n";
				break;
			}
			messageStr = "ko\n";
			break;
		case IncantationBgn:
			messageStr = "elevation en cours\n";
			break;
		case IncantationEnd:
			messageStr = "niveau actuel : " + std::to_string((dist2048(rng) % 8) + 1) ; //todo take level from player
			break;
		case ConnectNbr:
			messageStr = dist2048(rng);
			break;
		case Mort:
			messageStr = "mort\n";
			break;
		case Unknown:
			messageStr = "ko\n";
			break;
	}
}

Messages::~Messages() {}

std::string	&Messages::getMessageStr() {
	return messageStr;
}

Command	hashString(const std::string &str) {
	if (str == "avance") return Command::Avance;
	if (str == "droite") return Command::Droite;
	if (str == "gauche") return Command::Gauche;
	if (str == "voir") return Command::Voir;
	if (str == "inventaire") return Command::Inventaire;
	if (str == "prend") return Command::Prend;
	if (str == "pose") return Command::Pose;
	if (str == "expulse") return Command::Expulse;
	if (str == "broadcast") return Command::Broadcast;
	if (str == "incantation") return Command::IncantationBgn;
	if (str == "incantation_end") return Command::IncantationEnd;
	if (str == "fork") return Command::Fork;
	if (str == "connect_nbr") return Command::ConnectNbr;
	if (str == "mort") return Command::Mort;
	return Command::Unknown;
}
