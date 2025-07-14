#include "Team.hpp"

Team::Team()
{
}

Team::Team(std::string _name)
{
	this->name = _name;
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
