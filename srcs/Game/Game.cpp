#include "Game.hpp"

Game::Game()
{
}

Game::~Game() {
	for (auto& [fd, p] : playersfd_map) {
		if (p)
			delete p;
	}

	playersfd_map.clear();
}

std::map<int, Player *> &Game::get_players_map() {
	return this->playersfd_map;
}

void	Game::add_player_to_fdmap(int fd, Player *player) {
	playersfd_map.insert_or_assign(fd, player);
}

void Game::init_map(Parser *parser)
{
	int width  = parser->getWidth();
	int height = parser->getHeight();

	this->map.reserve(height);
	for (int i = 0; i < height; ++i)
		this->map.emplace_back(width);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			this->map[i][j].gen_resources();
			this->world_resources = this->world_resources + this->map[i][j].get_inv();
		}
	}
	std::cout << "Total World resources\n" << this->world_resources;
}

void Game::init_teams(Parser *parser)
{
	t_teams_names teamNames = parser->getTeamsNames();

	for (const auto& name : teamNames)
		this->teams[name] = Team(name);
}

Game::Game(Parser *parser)
{
	init_map(parser);
	init_teams(parser);

	// for (const auto& [name, team] : teams) {
	// 	std::cout << name << " -> " << team.get_name() << std::endl;
	// }
}

void Game::add_player_to_team(std::string team_name, Player *p)
{
	if (this->teams.find(team_name) == teams.end())
		return ;
	this->teams[team_name].add_player(p);
}

void Game::remove_player(Player *p)
{
	if (playersfd_map.find(p->get_sock_fd()) != playersfd_map.end())
		playersfd_map.erase(p->get_sock_fd());

	//remove player from tile
	
	for (auto& [name, team] : teams)
		team.remove_player(p);
	
	delete p;
	//std::cout << "Player deleted\n";
}
