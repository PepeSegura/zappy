#include "Game.hpp"

void Game::_Mort(Player *p)
{
	std::cout << "EXECUTING MORT\n";

	p->set_send_buffer("mort\n");
}
