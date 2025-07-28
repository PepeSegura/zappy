#pragma once

# include <vector>
# include <unordered_map>
# include <random>
# include "Inventory.hpp"
# include "Player.hpp"

enum class Item {
    NOURRITURE,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
};

const std::unordered_map<Item, double> item_densities = {
    {Item::NOURRITURE,	0.5},
    {Item::LINEMATE,	0.3},
    {Item::DERAUMERE,	0.15},
    {Item::SIBUR,		0.1},
    {Item::MENDIANE,	0.1},
    {Item::PHIRAS,		0.08},
    {Item::THYSTAME,	0.05}
};

const std::unordered_map<Item, const std::string> item_string = {
    {Item::NOURRITURE,	"Nourriture"},
    {Item::LINEMATE,	"Linemate"},
    {Item::DERAUMERE,	"Deraumere"},
    {Item::SIBUR,		"Sibur"},
    {Item::MENDIANE,	"Mendiane"},
    {Item::PHIRAS,		"Phiras"},
    {Item::THYSTAME,	"Thystame"}
};

class Tile {
	private:
		Inventory				inv;
		std::vector<Player*>	players;

	public:
		Tile() = default;
		~Tile() = default;
		Tile& operator=(const Tile& other) = default;

		std::vector<Player*>& get_players_list();
		Inventory&	get_inv(void);

		void		remove_player_from_team(Player*);
		void		add_player_to_team(Player*);

		std::string	aux_voir_tile(std::string item);
		std::string	voir_tile(Player*);
};

