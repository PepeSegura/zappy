#pragma once

# include <vector>
# include "Player.hpp"
# include "Inventory.hpp"

typedef std::chrono::high_resolution_clock::time_point timePoint;

class Player;

struct Incantation_Reqs {
	int		nbr_of_players, linemate_req,
			deraumere_req, sibur_req,
			mendiane_req, phiras_req,
			thystame_req;

	Incantation_Reqs() {};
	Incantation_Reqs(int players, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame) {
		this->nbr_of_players = players;
		this->linemate_req = linemate;
		this->deraumere_req = deraumere;
		this->sibur_req = sibur;
		this->mendiane_req = mendiane;
		this->phiras_req = phiras;
		this->thystame_req = thystame;
	};
};

class Incantation {
	public:
		Inventory				inv;
		int						level, x, y;
		std::vector<Player *>	players;
		timePoint				start;
		Incantation_Reqs		&requirements;
		bool					in_course;

		Incantation(Player *p, Incantation_Reqs &requirements, timePoint start);
		Incantation(const Incantation &other);
		~Incantation();
		Incantation &operator=(const Incantation &other);
		bool	isFilled() const;
		void	join(Player *p);
};
