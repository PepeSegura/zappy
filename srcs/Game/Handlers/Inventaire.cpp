#include "Game.hpp"

void Game::_Inventaire(Player *p)
{
	std::cout << "EXECUTING INVENTAIRE\n";

	std::cout << "Inventory: " << p->Inventaire() << std::endl;
	p->set_send_buffer(p->Inventaire());
}
