#include "Game.hpp"

void Game::_Droite(Player *p)
{
	std::string args = p->get_current_command().args;
	if (args.empty() == false) {
		this->_Unknown(p);
		return ;
	}
	std::cout << "EXECUTING DROITE\n";

	p->Droite();
	Messages rsp = Messages(Command::Droite, (void *) p, (void *) &map, true);
	p->set_send_buffer(rsp.getMessageStr());
	send2grclients(gr_player_pos(p->get_id()));
}
