#include "Game.hpp"

void Game::_Inventaire(Player *p)
{
	std::string args = p->get_current_command().args;
	if (args.empty() == false) {
		this->_Unknown(p);
		return ;
	}
	std::cout << "EXECUTING INVENTAIRE\n";

	std::cout << "Inventory: " << p->Inventaire() << std::endl;
	p->set_send_buffer(p->Inventaire());
}
