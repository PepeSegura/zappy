#include "Player.hpp"

void	Player::Prend(std::string item)
{
	this->inv.add_item(item, 1);
}

void	Player::Pose(std::string item)
{
	this->inv.add_item(item, -1);
}
