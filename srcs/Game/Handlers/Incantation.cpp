#include "Game.hpp"

void Game::_IncantationBgn(Player *p)
{
	std::cout << "EXECUTING INCANTATION\n";

	std::cout << "Checking prerequisites...\n";

	std::cout << "Checking materials...\n";
	if (!check_incantation_materials(p)){
		std::cout << "error: incantation: not enough materials\n";
		p->set_send_buffer("ko\n");
		return ;
	}

	std::cout << "Checking players...\n";
	if (!check_incantation_players_bgn(p)){
		std::cout << "error: incantation: players requisite not met\n";
		p->set_send_buffer("ko\n");
		return ;
	}

	std::cout << "All preliminary checks passed!\n";

	p->IncantationBgn();
}

void Game::_IncantationEnd(Player *p)
{
	std::cout << "EXECUTING INCANTATION_END\n";
	std::cout << "Checking end requisites...\n";

	if (!p->get_encantation_precheck()) {
		std::cout << "Checking materials...\n";
		if (!check_incantation_materials(p)){
			std::cout << "error: incantation: not enough materials\n";
			p->set_send_buffer("ko\n");
			return ;
		}
	
		std::cout << "Checking players...\n";
		if (!check_incantation_players_end(p)) {
	
			std::cout << "error: incantation: players requisite not met\n";
			p->set_send_buffer("ko\n");
			return ;
		}
		remove_incantation_materials(p);
		mark_all_enchanting_players(p);
	} else {
		std::cout << "Checks already done by another player\n";
		p->set_encantation_precheck(false);
	}

	std::cout << "All checks passed! Level up!\n";
	p->IncantationEnd();
}

bool Game::check_incantation_materials(Player *p) {
	Inventory &inv = map[p->get_y()][p->get_x()].get_inv();
	if (inv.get_linemate() < incantation_lvl_reqs[p->get_level()].linemate_req) {
		std::cout << "error: incantation: not enough linemate\n";
		return false;
	}
	if (inv.get_deraumere() < incantation_lvl_reqs[p->get_level()].deraumere_req) {
		std::cout << "error: incantation: not enough deraumere\n";
		return false;
	}
	if (inv.get_sibur() < incantation_lvl_reqs[p->get_level()].sibur_req) {
		std::cout << "error: incantation: not enough sibur\n";
		return false;
	}
	if (inv.get_mendiane() < incantation_lvl_reqs[p->get_level()].mendiane_req) {
		std::cout << "error: incantation: not enough mendiane\n";
		return false;
	}
	if (inv.get_phiras() < incantation_lvl_reqs[p->get_level()].phiras_req) {
		std::cout << "error: incantation: not enough phiras\n";
		return false;
	}
	if (inv.get_thystame() < incantation_lvl_reqs[p->get_level()].thystame_req) {
		std::cout << "error: incantation: not enough thystame\n";
		return false;
	}
	return true;
}

bool Game::check_incantation_players_bgn(Player *p) {
	if (map[p->get_y()][p->get_x()].players_at_level(p->get_level()) < incantation_lvl_reqs[p->get_level()].nbr_of_players)
		return false;
	return true;
}

bool Game::check_incantation_players_end(Player *p) {
	if (map[p->get_y()][p->get_x()].players_at_level_and_enchating(p->get_level()) < incantation_lvl_reqs[p->get_level()].nbr_of_players)
		return false;
	return true;
}

void Game::remove_incantation_materials(Player *p) {
	Inventory &inv = map[p->get_y()][p->get_x()].get_inv();

	if (incantation_lvl_reqs[p->get_level()].linemate_req) {
		inv.add_linemate(-incantation_lvl_reqs[p->get_level()].linemate_req);
	}
	if (incantation_lvl_reqs[p->get_level()].deraumere_req) {
		inv.add_deraumere(-incantation_lvl_reqs[p->get_level()].deraumere_req);
	}
	if (incantation_lvl_reqs[p->get_level()].sibur_req) {
		inv.add_sibur(-incantation_lvl_reqs[p->get_level()].sibur_req);
	}
	if (incantation_lvl_reqs[p->get_level()].mendiane_req) {
		inv.add_mendiane(-incantation_lvl_reqs[p->get_level()].mendiane_req);
	}
	if (incantation_lvl_reqs[p->get_level()].phiras_req) {
		inv.add_phiras(-incantation_lvl_reqs[p->get_level()].phiras_req);
	}
	if (incantation_lvl_reqs[p->get_level()].thystame_req) {
		inv.add_thystame(-incantation_lvl_reqs[p->get_level()].thystame_req);
	}
}

void Game::mark_all_enchanting_players(Player *p) {
	std::vector<Player *> players = map[p->get_y()][p->get_x()].get_players_list();

	for (auto other_p : players) {
		if (p != other_p && other_p->get_is_encantating() && p->get_level() == other_p->get_level())
			other_p->set_encantation_precheck(true);
	}
}
