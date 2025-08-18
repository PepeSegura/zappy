#include "Game.hpp"

void Game::_IncantationBgn(Player *p)
{
	std::string args = p->get_current_command().args;
	if (args.empty() == false) {
		this->_Unknown(p);
		return ;
	}
	std::cout << "EXECUTING INCANTATION\n";

	//join or create incantation
	bool joined = false;
	IncantationList &incantations = map[p->get_y()][p->get_x()].incantations[p->get_level()];
	for (auto &incantation : incantations) {
		if (!incantation.isFilled() && !incantation.in_course) { //join available incantation
			incantation.join(p);
			p->incantation = &incantation;
			joined = true;
			std::cout << "Joined an existing incantation(skiping materials check)\n";
			break ;
		}
	}

	if (!joined) { //if couldnt join, create a new one
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

		//create new incantation
		Incantation_Reqs &requirements = incantation_lvl_reqs[p->get_level()];
		Incantation incantation(p, requirements, now);
		incantation.join(p);
		size_t pos = incantations.size();
		incantations.push_back(Incantation(incantation));
		auto it = incantations.begin();
		std::advance(it, pos);
		p->incantation = &(*it); //incantations[pos]
		Inventory &tile_inv = map[p->get_y()][p->get_x()].get_inv();
		
		manage_incantation_inventory(tile_inv, requirements, -1);
		std::cout << "Created and joined a new incantation\n";
	}

	p->IncantationBgn(*(p->incantation));
}

void Game::_IncantationStart(Player *p)
{
	std::cout << "EXECUTING INCANTATION_START\n";
	if (p->incantationFailed) {
		std::cout << "incantation checked by other player; failed...\n";
		p->set_send_buffer("ko\n");
		p->incantationFailed = false;
		return ;
	}
	if (p->firstPrecheck) {
		std::cout << "incantation checked by other player\n";
		p->firstPrecheck = false;
		p->IncantationStart();
		return ;
	}
	std::cout << "Checking that all players have joined...\n";
	if (p->incantation->players.size() != (size_t)p->incantation->requirements.nbr_of_players) { // incantation failed
		std::cout << "incantation failed... not enough players\n";
		IncantationList &incantations = map[p->incantation->y][p->incantation->x].incantations[p->get_level()];
		size_t pos = 0;
		for (Incantation &incantation: incantations) {
			if (&incantation == p->incantation) {
				Inventory &tile_inv = map[p->incantation->y][p->incantation->x].get_inv();
				manage_incantation_inventory(tile_inv, p->incantation->requirements, 1);
				mark_players_incantationfailed(p);
				p->set_send_buffer("ko\n");
				auto it = incantations.begin();
				std::advance(it, pos);
				incantations.erase(it);
				return ;
			}
			++pos;
		}
	}
	mark_first_precheck(p);
	std::string playerIds;
	for (auto player : p->incantation->players) {
		playerIds += std::to_string(player->get_id()) + " ";
	}
	playerIds.pop_back();
	send2grclients(gr_incantation_start(p->incantation->y, p->incantation->y, p->incantation->level, playerIds));
	p->IncantationStart();
}

void Game::_IncantationEnd(Player *p)
{
	std::cout << "EXECUTING INCANTATION_END\n";
	std::cout << "Checking end requisites...\n";
	bool success = true;

	if (!p->get_encantation_precheck() && !p->incantationFailed) {
		std::cout << "Materials are inside incantation inventory; skipping\n";
	
		std::cout << "Checking players...\n";
		for (Player *incantationPlayer : p->incantation->players) {
			if (incantationPlayer->get_y() != p->incantation->y || incantationPlayer->get_x() != p->incantation->x) {
				success = false;
				break ;
			}
		}
		if (p->incantation->players.size() != (size_t)p->incantation->requirements.nbr_of_players) {
			std::cout << "Incantation failed: Not enough players joined the incantation...\n";
			success = false;
		}

		IncantationList &incantations = map[p->incantation->y][p->incantation->x].incantations[p->get_level()];
		size_t pos = 0;
		for (Incantation &incantation: incantations) {
			if (&incantation == p->incantation) {
				if (!success) {
					Inventory &tile_inv = map[p->incantation->y][p->incantation->x].get_inv();
					manage_incantation_inventory(tile_inv, p->incantation->requirements, 1);
					mark_players_incantationfailed(p);
					p->set_send_buffer("ko\n");
					auto it = incantations.begin();
					std::advance(it, pos);
					incantations.erase(it);
					send2grclients(gr_incantation_res(p->incantation->y, p->incantation->x, 0));
					for (auto player : p->incantation->players) {
						send2grclients(gr_player_lvl(player->get_id(), false));
					}
					send2grclients(gr_content_tile(p->incantation->y, p->incantation->x));
					return ;
				}
				
				manage_incantation_inventory(world_resources, p->incantation->requirements, -1);
				send2grclients(gr_incantation_res(p->incantation->y, p->incantation->x, 1));
				for (auto player : p->incantation->players) {
					send2grclients(gr_player_lvl(player->get_id(), true));
				}
				send2grclients(gr_content_tile(p->incantation->y, p->incantation->x));
				auto it = incantations.begin();
				std::advance(it, pos);
 				incantations.erase(it);
				break ;
			}
			++pos;
		}
		mark_all_enchanting_players(p);
	} else if (p->get_encantation_precheck()) {
		std::cout << "Checks already done by another player\n";
		p->set_encantation_precheck(false);
	} else if (p->incantationFailed) {
		std::cout << "Checks already done by another player and failed\n";
		p->set_send_buffer("ko\n");
		p->incantationFailed = false;
		return ;
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

void Game::mark_all_enchanting_players(Player *p) {
	std::vector<Player *> players = map[p->get_y()][p->get_x()].get_players_list();

	for (auto other_p : players) {
		if (p != other_p && other_p->get_is_encantating() && p->get_level() == other_p->get_level() && p->incantation == other_p->incantation)
			other_p->set_encantation_precheck(true);
	}
}

void Game::mark_players_incantationfailed(Player *p) {
	std::vector<Player *> players = map[p->get_y()][p->get_x()].get_players_list();

	for (auto other_p : players) {
		if (p != other_p && other_p->get_is_encantating() && p->get_level() == other_p->get_level() && p->incantation == other_p->incantation)
			other_p->incantationFailed = true;
	}
}

void Game::mark_first_precheck(Player *p) {
	std::vector<Player *> players = map[p->get_y()][p->get_x()].get_players_list();

	for (auto other_p : players) {
		if (p != other_p && other_p->get_is_encantating() && p->get_level() == other_p->get_level() && p->incantation == other_p->incantation)
			other_p->firstPrecheck = true;
	}
}

void Game::manage_incantation_inventory(Inventory &inv, Incantation_Reqs &requirements,int sign) {
	inv.add_linemate(sign * requirements.linemate_req);
	inv.add_deraumere(sign * requirements.deraumere_req);
	inv.add_phiras(sign * requirements.phiras_req);
	inv.add_sibur(sign * requirements.sibur_req);
	inv.add_thystame(sign * requirements.thystame_req);
	inv.add_mendiane(sign * requirements.mendiane_req);
}