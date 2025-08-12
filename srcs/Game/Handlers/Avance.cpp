#include "Game.hpp"

void Game::_Avance(Player *p)
{
	std::string args = p->get_current_command().args;
	if (args.empty() == false) {
		this->_Unknown(p);
		return ;
	}
	std::cout << "EXECUTING AVANCE\n";

	this->map[p->get_y()][p->get_x()].remove_player_from_team(p);
	p->Avance();
	this->map[p->get_y()][p->get_x()].add_player_to_team(p);
	Messages rsp = Messages(Command::Avance, (void *) p, (void *) &map, true);
	p->set_send_buffer(rsp.getMessageStr());
	send2grclients(gr_player_pos(p->get_id()));
}
