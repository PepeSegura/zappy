#pragma once

# include <iostream>
# include <vector>
# include <string>

# include "FlagParser.hpp"

typedef std::vector<std::string> t_teams_names;
# define GRAPHIC_NAME "GRAPHIC"

class Parser {
	private:
		int				port;
		int				x; // width
		int				y; // height
		t_teams_names	teams_names;
		int				teams_members_limit;
		int				time_freq;
		bool			debug;

	public:
		Parser(int argc, char **argv);
		~Parser();

		void setPort(t_flag_parser *flags, int pos_flag);
		void setWidth(t_flag_parser *flags, int pos_flag);
		void setHeight(t_flag_parser *flags, int pos_flag);
		void setTeamsMembersLimit(t_flag_parser *flags, int pos_flag);
		void setTeams(t_flag_parser *flags, int pos_flag);
		void setTimeFreq(t_flag_parser *flags, int pos_flag);
		void setDebug();

		void settersParser(t_flag_parser *flags);

		int getPort(void) const;
		int getWidth(void) const;
		int getHeight(void) const;
		int getTeamsMembersLimit(void) const;
		int getTimeFreq(void) const;
		bool	getDebug() const { return (this->debug); }
		t_teams_names getTeamsNames(void) const;
};


# define USAGE "Usage: ./server -p <port> -x <width> -y <height> -n <team> [<team>] [<team>] ... -c <nb> -t <t>\n\
-p port number\n\
-x world width\n\
-y world height\n\
-n team_name_1 team_name_2 ...\n\
-c number of clients authorized at the beginning of the game\n\
-t time unit divider (the greater t is, the faster the game will go)\n\
"
