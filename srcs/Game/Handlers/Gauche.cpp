#include "Game.hpp"

void Game::_Gauche(Player *p)
{
	std::cout << "EXECUTING GAUCHE\n";

	p->Gauche();
	Messages rsp = Messages(Command::Gauche, (void *) p, (void *) &map, true);
	p->set_send_buffer(rsp.getMessageStr());
	send2grclients(gr_player_pos(p->get_id()));
}
