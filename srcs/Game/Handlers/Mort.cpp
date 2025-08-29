#include "Game.hpp"

void Game::_Mort(Player *p)
{
	std::cout << "EXECUTING MORT\n";
	
	p->set_send_buffer("mort\n");
	if (p->get_handshake())
		send2grclients(gr_player_mort(p->get_id()));
	else
		send2grclients(gr_egg_mort(p->get_id()));
	if (p->get_disconnected()) { remove_player(p); }
}
