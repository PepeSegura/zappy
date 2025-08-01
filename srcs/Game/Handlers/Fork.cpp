#include "Game.hpp"

void Game::_Fork(Player *p)
{
	std::cout << "EXECUTING FORK\n";

	Player *egg = new Player(p->get_team_name());

	egg->set_x(p->get_x());
	egg->set_y(p->get_y());

	this->teams[p->get_team_name()].inc_max_conns();
	this->teams[p->get_team_name()].add_player(egg);
	this->map[p->get_y()][p->get_x()].add_player_to_team(egg);

	p->set_send_buffer("ok\n");
}
