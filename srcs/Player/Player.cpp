#include "Player.hpp"

Player::Player()
{
	this->inv = Inventory();
	this->handshake_finished = false;
	this->dead = false;
}

Player::~Player()
{
}

Player::Player(std::string team)
{
	this->team_name = team;
	this->handshake_finished = false;
	this->dead = false;
}

Player&  Player::operator=(const Player &other)
{
	this->team_name = other.team_name;
	this->inv = other.inv;
	this->level = other.level;
	this->dir = other.dir;
	this->x = other.x;
	this->y = other.y;
	this->dead = other.dead;
	this->handshake_finished = other.handshake_finished;

	this->sock_fd = other.sock_fd;
	this->state = other.state;

	this->send_buffer = other.send_buffer;
	this->msg_to_parse = other.msg_to_parse;
	this->recv_buffer = other.recv_buffer;
	this->command_queue = other.command_queue;
	return (*this);
}

void Player::parse_msg()
{
	if (!this->msg_to_parse.empty() && this->msg_to_parse.back() == '\n')
		this->msg_to_parse.pop_back();
	std::cout << "Adding: [" << this->msg_to_parse << "]\n";

	this->add_command(this->msg_to_parse);
	this->msg_to_parse.clear();
}

void	Player::add_buffer_or_parse_msg(std::string buffer)
{
	size_t nl_pos = buffer.find("\n");
	if (nl_pos == std::string::npos) // newline not found == ADD_BUFFER
	{
		this->recv_buffer += buffer;
		return ;
	}
	this->recv_buffer += buffer.substr(0, nl_pos + 1); // append to buffer until nl
	this->msg_to_parse = this->recv_buffer; // copy msg to msg_to_parse
	this->recv_buffer.clear();
	this->parse_msg();
	buffer = buffer.substr(nl_pos + 1);
	this->add_buffer_or_parse_msg(buffer);
}

void	Player::Eat()
{
	if (this->inv.get_nourriture() == 0)
		this->dead = true;
	this->inv.add_nourriture(-1);
}

void	Player::Avance()
{
	switch (this->dir)
	{
		case 'N':
			this->y--;
			break;		
		case 'S':
			this->y++;
			break;
		case 'W':
			this->x--;
			break;
		case 'E':
			this->x++;
			break;
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
	return (inv_str += "}");
}

void	Player::Prend(std::string item)
{
	if (item == "nourriture")	this->inv.add_nourriture(1);
	if (item == "linemate")		this->inv.add_linemate(1);
	if (item == "deraumere")	this->inv.add_deraumere(1);
	if (item == "sibur")		this->inv.add_sibur(1);
	if (item == "mendiane")		this->inv.add_mendiane(1);
	if (item == "phiras")		this->inv.add_phiras(1);
	if (item == "thystame")		this->inv.add_thystame(1);
}

void	Player::Pose(std::string item)
{
	if (item == "nourriture")	this->inv.add_nourriture(-1);
	if (item == "linemate")		this->inv.add_linemate(-1);
	if (item == "deraumere")	this->inv.add_deraumere(-1);
	if (item == "sibur")		this->inv.add_sibur(-1);
	if (item == "mendiane")		this->inv.add_mendiane(-1);
	if (item == "phiras")		this->inv.add_phiras(-1);
	if (item == "thystame")		this->inv.add_thystame(-1);
}

void	Player::IncantationBgn()
{
	/* set flag so he cannot move?? */
}

void	Player::IncantationEnd()
{
	this->level++;
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

void	Player::add_command(std::string trimmed_cmd) {
	if (command_queue.size() < 10) {
		size_t pos = trimmed_cmd.find(" ");
		Command_Data tmp;
		if (pos < trimmed_cmd.length()){
			tmp.args = trimmed_cmd.substr(pos + 1);
			trimmed_cmd = trimmed_cmd.substr(0, pos);
		}
		tmp.cmd = hashString(trimmed_cmd);
		command_queue.emplace_back(tmp);
	}
	std::cout << "After adding: \n";
	for (auto action : command_queue){
		std::cout << action.cmd << ";" << action.args << std::endl;
	}
}