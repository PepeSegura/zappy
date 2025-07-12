#pragma once

# include <iostream>
# include "Inventory.hpp"

class Inventory;

class Player
{
	private:
		std::string team_name;
		Inventory	inv;
		int			level;
		int			x;
		int			y;

		int			sock_fd;
		int			state;


	public:
		Player();
		Player(std::string);
		~Player();

		Player&  operator=(const Player &other);

		std::string	get_team_name() const;
		Inventory	get_inv() const;
		int			get_level() const;
		int			get_x() const;
		int			get_y() const;
		int			get_sock_fd() const;
		int			get_state() const;

		void		set_level(int);
		void		set_x(int);
		void		set_y(int);
		void		set_sock_fd(int);
		void		set_state(int);
};
