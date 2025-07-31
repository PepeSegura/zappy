#include "Player.hpp"
#include "Game.hpp"

void	Player::Eat()
{
	if (this->inv.get_nourriture() == 0)
		this->dead = true;
	this->inv.add_nourriture(-1);
}

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

void	Player::Prend(std::string item)
{
	this->inv.add_item(item, 1);
}

void	Player::Pose(std::string item)
{
	this->inv.add_item(item, -1);
}

void	Player::IncantationBgn()
{
	is_encantating = true;
	encantation_prechecked = false;
	Command_Data IncantationEndCmd;
	IncantationEndCmd.cmd = Command::IncantationEnd;
	IncantationEndCmd.cmd_name = "incantation_end";

	command_queue.insert(command_queue.begin() + 1, IncantationEndCmd);
	send_buffer = "elevation en cours\n";
}

void	Player::IncantationEnd()
{
	this->level++;
	send_buffer = "niveau actuel : "+ std::to_string(level) +"\n";
	is_encantating = false;
}
