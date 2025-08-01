#include "Player.hpp"

void	Player::Droite()
{
	switch (this->dir)
	{
		case 'N':
			this->dir = 'E';
			break;		
		case 'S':
			this->dir = 'W';
			break;
		case 'W':
			this->dir = 'N';
			break;
		case 'E':
			this->dir = 'S';
			break;
		default:
			break;
	}
}
