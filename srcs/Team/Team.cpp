#include "Team.hpp"
#include "Game.hpp"
#include "Tile.hpp"

Team::Team()
{
	game = nullptr;
}

Team::Team(std::string _name, int _max_conns, Game *game)
{
	this->name = _name;
	this->max_conns = _max_conns;
	this->game = game;
}

Team::~Team()
{
	for (auto player : players) {
		if (!player->get_handshake())
			delete player;
	}
}

void	Team::add_player(Player* player)
{
	if (player == nullptr)
		return ;

	auto it = std::find(this->players.begin(), this->players.end(), player);
	if (it != this->players.end())
		return ;
	this->players.push_back(player);
	// std::cout << "Team[\"" << this->name << "\"] -> size: " << this->players.size() << std::endl;
}

void	Team::remove_player(Player* player)
{
	if (player == nullptr)
		return ;

	auto it = std::find(this->players.begin(), this->players.end(), player);
	if (it == this->players.end())
		return ;
	this->players.erase(it);
	if (max_conns) --max_conns;
	if (conns_nbr) --conns_nbr;
	// std::cout << "Team[\"" << this->name << "\"] -> size: " << this->players.size() << std::endl;
}

std::string	Team::get_name() const
{
	return (this->name);
}

uint32_t	Team::get_conns_nbr() const {
	return this->conns_nbr;
}

uint32_t	Team::get_max_conns() const {
	return this->max_conns;
}

uint32_t	Team::get_avail_conns() const {
	int cnt = 0;
	for (uint32_t i = 0; i < max_conns; ++i) {
		Player *p = players[i];
		if (p->get_disconnected() && p->is_hatched())
			++cnt;
	}
	return cnt;
}

void	Team::init_eggs(int width, int height) {
	for (uint32_t i = 0; i < max_conns; ++i) {
		int x = Utils::random_between(0, width - 1);
		int y = Utils::random_between(0, height - 1);

		Player *egg = new Player(name, std::chrono::system_clock::from_time_t(0), game);
		egg->set_x(x);
		egg->set_y(y);
		add_player(egg);
		this->game->get_tile_map()[y][x].add_player_to_team(egg);
		// std::cout << "Added egg " << std::to_string(i) << " to team " << name << std::endl;
	}
	conns_nbr = 0;
}

void	Team::inc_conns_nbr() {
	++conns_nbr;
}

void	Team::dec_conns_nbr() {
	if (conns_nbr) --conns_nbr;
}

void	Team::inc_max_conns() {
	++max_conns;
}

void	Team::dec_max_conns() {
	--max_conns;
}

Player	*Team::player2egg(Player *p) {
	Player *egg;
	if (get_avail_conns() <= 0)
		return nullptr;
	for (uint32_t i = 0; i < max_conns; ++i) {
		egg = players[i];
		if (egg->get_disconnected() && egg->is_hatched())
			break ;
	}
	egg->handshake(p);
	++conns_nbr;
	return egg;
}

std::vector<Player*>	&Team::get_team_players() {
	return (this->players);
}
