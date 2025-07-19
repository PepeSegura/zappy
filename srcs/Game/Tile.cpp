# include "Tile.hpp"
# include <algorithm>

Inventory& Tile::get_inv(void)
{
	return (this->inv);
}

void Tile::gen_item(Item item)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> dist(0.0, 1.0);

	if (dist(gen) < item_densities.at(item)) {
		switch (item)
		{
			case Item::NOURRITURE:
				this->inv.add_nourriture(1);
				break;
			case Item::LINEMATE:
				this->inv.add_linemate(1);
				break;
			case Item::DERAUMERE:
				this->inv.add_deraumere(1);
				break;
			case Item::SIBUR:
				this->inv.add_sibur(1);
				break;
			case Item::MENDIANE:
				this->inv.add_mendiane(1);
				break;
			case Item::PHIRAS:
				this->inv.add_phiras(1);
				break;
			case Item::THYSTAME:
				this->inv.add_thystame(1);
				break;
			default:
				break;
		}
	}
}

void Tile::gen_resources(void)
{
	gen_item(Item::NOURRITURE);
	gen_item(Item::LINEMATE);
	gen_item(Item::DERAUMERE);
	gen_item(Item::SIBUR);
	gen_item(Item::MENDIANE);
	gen_item(Item::PHIRAS);
	gen_item(Item::THYSTAME);
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
