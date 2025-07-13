#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init_map(Parser *parser)
{
	int width  = parser->getWidth();
	int height = parser->getHeight();

	this->map.reserve(height);
	for (int i = 0; i < height; ++i)
		this->map.emplace_back(width);
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

void Game::add_player(std::string team_name, Player *p)
{
	if (this->teams.find(team_name) == teams.end())
		return ;
	this->teams[team_name].add_player(p);
}

void Game::remove_player(Player *p)
{
	for (auto& [name, team] : teams)
		team.remove_player(p);
}
