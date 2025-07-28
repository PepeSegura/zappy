# include "Tile.hpp"
# include "Game.hpp"
# include <algorithm>

Inventory& Tile::get_inv(void)
{
	return (this->inv);
}

std::vector<Player*>& Tile::get_players_list()
{
	return (this->players);
}

void	Tile::remove_player_from_team(Player *p)
{
	auto it = std::find(this->players.begin(), this->players.end(), p);

	if (it != this->players.end())
		this->players.erase(it);
}

void	Tile::add_player_to_team(Player *p)
{
	auto it = std::find(this->players.begin(), this->players.end(), p);

	if (it == this->players.end())
		this->players.push_back(p);
}

std::string Tile::aux_voir_tile(std::string item)
{
	std::string content_tile;

	// std::cout << "Getting [" << item << "]: " << this->inv.get_item(item) << std::endl;
	for (int i = 0; i < this->inv.get_item(item); ++i)
		content_tile += " " + item;
	return (content_tile);
}

std::string Tile::voir_tile(Player *p)
{
	std::string content_tile;

	for (Player* player : players)
	{
		if (player == p)
			continue;
		if (player->get_disconnected() == true)
			content_tile += " egg";
		else
			content_tile += " player";
	}

	content_tile += aux_voir_tile("nourriture");
	content_tile += aux_voir_tile("linemate");
	content_tile += aux_voir_tile("deraumere");
	content_tile += aux_voir_tile("sibur");
	content_tile += aux_voir_tile("mendiane");
	content_tile += aux_voir_tile("phiras");
	content_tile += aux_voir_tile("thystame");

	if (content_tile.length() > 1)
		content_tile.erase(0, 1);

	// std::cout << "Content_tile: [" << content_tile << "]" <<std::endl;
	return (content_tile);
}
