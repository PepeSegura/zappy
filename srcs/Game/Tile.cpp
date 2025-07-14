# include "Tile.hpp"

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
