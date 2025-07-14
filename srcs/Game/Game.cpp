#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

std::map<int, Player *> &Game::get_players_map() {
	return this->playersfd_map;
}

void	Game::add_player_to_fdmap(int fd, Player *player) {
	playersfd_map[fd] = player;
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
	playersfd_map[p->get_sock_fd()] = nullptr;

	for (auto& [name, team] : teams)
		team.remove_player(p);
}
