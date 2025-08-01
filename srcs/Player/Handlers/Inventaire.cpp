#include "Player.hpp"

static	std::string aux_inv(std::string key, int value)
{
	return (key + std::to_string(value) + ", ");
}

std::string	Player::Inventaire()
{
	std::string inv_str = "{";

	inv_str += aux_inv("nourriture ", this->inv.get_nourriture());
	inv_str += aux_inv("linemate ", this->inv.get_linemate());
	inv_str += aux_inv("deraumere ", this->inv.get_deraumere());
	inv_str += aux_inv("sibur ", this->inv.get_sibur());
	inv_str += aux_inv("mendiane ", this->inv.get_mendiane());
	inv_str += aux_inv("phiras ", this->inv.get_phiras());
	inv_str += aux_inv("thystame ", this->inv.get_thystame());

	if (inv_str.size() > 1)
	{
		inv_str.erase(inv_str.end() - 1);
		inv_str.erase(inv_str.end() - 1);
	}
	return (inv_str += "}\n");
}
