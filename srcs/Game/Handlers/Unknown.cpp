#include "Game.hpp"

void Game::_Unknown(Player *p)
{
	std::cout << "IGNORING UNKNOWN COMMAND\n";

	p->set_send_buffer("ko\n");
}
