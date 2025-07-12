#include "Player.hpp"

Player::Player()
{
	std::cout << "Player()\n";
	this->inv = Inventory();
}

Player::~Player()
{
	std::cout << "~Player()\n";
}

Player::Player(std::string team)
{
	std::cout << "~Player(std::string name)\n";
	this->team_name = team;
}

Player&  Player::operator=(const Player &other)
{
	this->team_name = other.team_name;
	this->inv = other.inv;
	this->level = other.level;
	this->x = other.x;
	this->y = other.y;

	this->sock_fd = other.sock_fd;
	this->state = other.state;
	return (*this);
}

/*_____GETTERS_____*/

std::string	Player::get_team_name() const
{
	return (this->team_name);
}

Inventory	Player::get_inv() const
{
	return (this->inv);
}

int	Player::get_level() const
{
	return (this->level);
}

int	Player::get_x() const
{
	return (this->x);
}

int	Player::get_y() const
{
	return (this->y);
}

int	Player::get_sock_fd() const
{
	return (this->sock_fd);
}

int	Player::get_state() const
{
	return (this->state);
}

/*_____SETTERS_____*/

void	Player::set_level(int new_level)
{
	this->level = new_level;
}

void	Player::set_x(int new_x)
{
	this->x = new_x;
}

void	Player::set_y(int new_y)
{
	this->y = new_y;
}

void	Player::set_sock_fd(int new_sock_fd)
{
	this->sock_fd = new_sock_fd;
}

void	Player::set_state(int new_state)
{
	this->state = new_state;
}
