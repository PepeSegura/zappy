#include "Player.hpp"

void	Player::Eat()
{
	if (this->inv.get_nourriture() == 0)
		this->dead = true;
	this->inv.add_nourriture(-1);
}
