#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

std::map<int, Player *> &Game::get_players_map() {
	return this->players_map;
}

void	Game::add_player_to_map(int fd, Player *player) {
	players_map[fd] = player;
}