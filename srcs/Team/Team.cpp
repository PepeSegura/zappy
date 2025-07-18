#include "Team.hpp"

Team::Team()
{
}

Team::Team(std::string _name, int _max_conns)
{
	this->name = _name;
	this->max_conns = _max_conns;
}

Team::~Team()
{
}

void	Team::add_player(Player* player)
{
	if (player == nullptr)
		return ;

	auto it = std::find(this->players.begin(), this->players.end(), player);
	if (it != this->players.end())
		return ;
	this->players.push_back(player);
	std::cout << "Team[\"" << this->name << "\"] -> size: " << this->players.size() << std::endl;
}

void	Team::remove_player(Player* player)
{
	if (player == nullptr)
		return ;

	auto it = std::find(this->players.begin(), this->players.end(), player);
	if (it == this->players.end())
		return ;
	this->players.erase(it);
	std::cout << "Team[\"" << this->name << "\"] -> size: " << this->players.size() << std::endl;
}

std::string	Team::get_name() const
{
	return (this->name);
}

uint32_t	Team::get_conns_nbr() const {
	return this->conns_nbr;
}

uint32_t	Team::get_max_conns() const {
	return this->max_conns;
}

void	Team::init_eggs(int width, int height) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist2048(0,2047);
	for (int i = 0; i < max_conns; ++i) {
		Player *p = new Player(name);
		int x = dist2048(rng) % width;
		int y = dist2048(rng) % height;
		p->set_x(x);
		p->set_y(y);
		//maybe set random dir?
		add_player(p);
		std::cout << "Added egg " << std::to_string(i) << " to team " << name << std::endl;
	}
	conns_nbr = 0;
}

void	Team::inc_conns() {
	++conns_nbr;
}

void	Team::dec_conns() {
	--conns_nbr;
}

Player	*player2egg(Player *p) {
	
}
