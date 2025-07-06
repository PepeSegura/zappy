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


		/* data */
	public:
		Player();
		~Player();
};
