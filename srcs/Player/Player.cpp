#include "Player.hpp"

Player::Player()
{
	this->inv = Inventory();
	this->handshake_finished = false;
}

Player::~Player()
{
}

Player::Player(std::string team)
{
	this->team_name = team;
	this->handshake_finished = false;
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

std::string	Player::get_recv_buffer() const
{
	return (this->recv_buffer);
}

std::string	Player::get_send_buffer() const
{
	return (this->send_buffer);
}

Inventory&	Player::get_inv()
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

bool	Player::get_handshake() const
{
	return (this->handshake_finished);
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

void	Player::set_team_name(std::string &team_name)
{
	this->team_name = team_name;
}

void	Player::set_recv_buffer(std::string &buffer)
{
	this->recv_buffer = buffer;
}

void	Player::set_send_buffer(std::string &buffer)
{
	this->send_buffer = buffer;
}

void	Player::set_handshake(bool &status)
{
	this->handshake_finished = status;
}