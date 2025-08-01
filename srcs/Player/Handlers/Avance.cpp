#include "Player.hpp"
#include "Game.hpp"

void	Player::Avance()
{
	if (this->game_ptr == nullptr)
	{
		std::cerr << "Game PTR not set\n";
		return ;
	}
	std::cout << "Avance towards: " << this->dir << std::endl;

	int map_width = this->game_ptr->get_map_width();
	int map_height = this->game_ptr->get_map_height();

	switch (this->dir)
	{
		case 'N':
		{
			if (this->y - 1 == -1)
				this->y = map_height - 1;
			else
				this->y--;
			break;		
		}
		case 'S':
		{
			if (this->y + 1 == map_height)
				this->y = 0;
			else
				this->y++;
			break;		
		}
		case 'W':
		{
			if (this->x - 1 == -1)
				this->x = map_width - 1;
			else
				this->x--;
			break;		
		}
		case 'E':
		{
			if (this->x + 1 == map_width)
				this->x = 0;
			else
				this->x++;
			break;		
		}
		default:
			break;
	}
}
