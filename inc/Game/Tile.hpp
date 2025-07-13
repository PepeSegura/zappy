#pragma once

# include <vector>
# include "Inventory.hpp"
# include "Player.hpp"

class Tile {
	private:
		Inventory				inv;
		std::vector<Player*>	players;

	public:
		Tile() = default;
		~Tile() = default;
		Tile& operator=(const Tile& other) = default;

		Inventory& get_inv(void);
};

