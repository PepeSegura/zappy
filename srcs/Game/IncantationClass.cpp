#include "Incantation.hpp"


Incantation::Incantation(Player *p, Incantation_Reqs &requirements, timePoint start) : requirements(requirements) {
	this->level = p->get_level();
	this->start = start;
	this->inv.add_linemate(requirements.linemate_req);
	this->inv.add_deraumere(requirements.deraumere_req);
	this->inv.add_phiras(requirements.phiras_req);
	this->inv.add_sibur(requirements.sibur_req);
	this->inv.add_thystame(requirements.thystame_req);
	this->inv.add_mendiane(requirements.mendiane_req);
	y = p->get_y();
	x = p->get_x();
	in_course = false;
}

Incantation::Incantation(const Incantation &other) : requirements(other.requirements) {
	this->inv = other.inv;
	this->level = other.level;
	this->players = other.players;
	this->start = other.start;
	this->x = other.x;
	this->y = other.y;
	this->in_course = other.in_course;
}

Incantation::~Incantation() {}

Incantation &Incantation::operator=(const Incantation &other) {
	this->inv = other.inv;
	this->level = other.level;
	this->players = other.players;
	this->start = other.start;
	this->requirements = other.requirements;
	this->x = other.x;
	this->y = other.y;
	this->in_course = other.in_course;

	return *this;
}

bool	Incantation::isFilled() const {
	return (size_t)this->requirements.nbr_of_players == this->players.size();
}

void Incantation::join(Player *p) {
	players.push_back(p);
}

void Incantation::remove(Player *p) {
	auto it = std::find(players.begin(), players.end(), p);
	if (it != players.end()) {
		players.erase(it);
	}
}
