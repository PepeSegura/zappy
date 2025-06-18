#pragma once

# include <iostream>
# include <vector>

# include "FlagParser.hpp"

typedef std::vector<std::string> t_teams_names;

class Parser {
	private:
		int				port;
		int				x;
		int				y;
		int				authorized_clients;
		int				time_div;
		t_teams_names	teams_names;

	public:
		Parser(int argc, char **argv);
		~Parser();
		void settersParser(t_flag_parser *flags);
};


# define USAGE "Usage: ./server -p <port> -x <width> -y <height> -n <team> [<team>] [<team>] ... -c <nb> -t <t>\n\
-p port number\n\
-x world width\n\
-y world height\n\
-n team_name_1 team_name_2 ...\n\
-c number of clients authorized at the beginning of the game\n\
-t time unit divider (the greater t is, the faster the game will go)\n\
"
