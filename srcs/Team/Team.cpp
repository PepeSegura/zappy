#include "Team.hpp"

Team::Team()
{
}

Team::~Team()
{
}

void	Team::addPlayer(Player* player)
{
	if (player == nullptr)
		return ;

	auto it = std::find(this->players.begin(), this->players.end(), player);
	if (it != this->players.end())
		return ;
	this->players.push_back(player);
	std::cout << "Team_size: " << this->players.size() << std::endl;
}

void	Team::removePlayer(Player* player)
{
	if (player == nullptr)
		return ;

	auto it = std::find(this->players.begin(), this->players.end(), player);
	if (it == this->players.end())
		return ;
	this->players.erase(it);
	std::cout << "Team_size: " << this->players.size() << std::endl;
}
