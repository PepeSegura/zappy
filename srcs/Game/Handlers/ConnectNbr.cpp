#include "Game.hpp"

void Game::_ConnectNbr(Player *p)
{
	std::cout << "EXECUTING CONNECT_NBR\n";

	uint32_t conn_nbr = this->teams[p->get_team_name()].get_avail_conns();
	p->set_send_buffer(std::to_string(conn_nbr) + "\n");
}
