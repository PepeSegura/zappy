#include "Player.hpp"

void	Player::Gauche()
{
	switch (this->dir)
	{
		case 'N':
			this->dir = 'W';
			break;		
		case 'S':
			this->dir = 'E';
			break;
		case 'W':
			this->dir = 'S';
			break;
		case 'E':
			this->dir = 'N';
			break;
		default:
			break;
	}
}
