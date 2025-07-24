#pragma once

# include <vector>
# include <algorithm>
# include "Player.hpp"

class Team
{
	private:
		std::string name;
		std::vector<Player*>	players;
		uint32_t				conns_nbr;
		uint32_t				max_conns;
		Game					*game;

	public:
		Team();
		Team(std::string _name, int _max_conns, Game *);
		~Team();

		std::string	get_name() const;
		uint32_t	get_conns_nbr() const;
		uint32_t	get_max_conns() const;
		uint32_t	get_avail_conns() const;
		void		add_player(Player* player);
		void		remove_player(Player* player);
		void		init_eggs(int , int);
		void		inc_conns_nbr();
		void		dec_conns_nbr();
		void		inc_max_conns();
		void		dec_max_conns();
		Player		*player2egg(Player *);

		std::vector<Player*>	&get_team_players();
};


