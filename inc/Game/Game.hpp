#pragma once

# include <map>
# include <iostream>
# include "Team.hpp"

class Game
{
	private:
		std::map<std::string, Team*> teams;

	public:
		Game();
		~Game();
};
