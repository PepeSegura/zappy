#include "Parser.hpp"

void Parser:: setPort(t_flag_parser *flags, int pos_flag) {
	if (flags->flags[pos_flag].args_count != 1) {
		std::cerr << "server: invalid number of ports" << std::endl;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
	try {
		this->port = std::stoi(flags->flags[pos_flag].args[0]);
	}
	catch (const std::exception &e) {
		std::cerr << "server: invalid port '" << flags->flags[pos_flag].args[0] << "'" << std::endl;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
	if (this->port < 0 || this->port > 65535) {
		std::cerr << "server: invalid port '" << flags->flags[pos_flag].args[0] << "'" << std::endl;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
}

void Parser:: setWidth(t_flag_parser *flags, int pos_flag) {
	if (flags->flags[pos_flag].args_count != 1) {
		std::cerr << "server: only 1 map width is allowed" << std::endl;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
	try {
		this->x = std::stoi(flags->flags[pos_flag].args[0]);
	}
	catch (const std::exception &e) {
		std::cerr << "server: invalid width '" << flags->flags[pos_flag].args[0] << "'" << std::endl;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
	if (this->x < 1 || this->x > 1024) {
		std::cerr << "server: invalid width '" << flags->flags[pos_flag].args[0] << "'" << std::endl;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
}

void Parser:: setHeight(t_flag_parser *flags, int pos_flag) {
	if (flags->flags[pos_flag].args_count != 1) {
		std::cerr << "server: only 1 map height is allowed" << std::endl;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
	try {
		this->y = std::stoi(flags->flags[pos_flag].args[0]);
	}
	catch (const std::exception &e) {
		std::cerr << "server: invalid height '" << flags->flags[pos_flag].args[0] << "'" << std::endl;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
	if (this->y < 1 || this->y > 1024) {
		std::cerr << "server: invalid height '" << flags->flags[pos_flag].args[0] << "'" << std::endl;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
}

void Parser:: setTeamsMembersLimit(t_flag_parser *flags, int pos_flag) {
	if (flags->flags[pos_flag].args_count != 1) {
		std::cerr << "server: only 1 number of clients authorized is allowed" << std::endl;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
	try {
		this->teams_members_limit = std::stoi(flags->flags[pos_flag].args[0]);
	}
	catch (const std::exception &e) {
		std::cerr << "server: invalid number of clients authorized '" << flags->flags[pos_flag].args[0] << "'" << std::endl;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
	if (this->teams_members_limit < 1) {
		std::cerr << "server: invalid number of clients authorized '" << flags->flags[pos_flag].args[0] << "'" << std::endl;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
}

void Parser:: setTeams(t_flag_parser *flags, int pos_flag) {
	size_t count = flags->flags[pos_flag].args_count;
	for (size_t i = 0; i < count; i++)
	{
		if (flags->flags[pos_flag].args[i] == std::string(GRAPHIC_NAME)) {
			std::cerr << "server: \"" << flags->flags[pos_flag].args[i] << "\" invalid team name" << std::endl;
			cleanup_parser(flags);
			exit(EXIT_FAILURE);
		}
		this->teams_names.push_back(flags->flags[pos_flag].args[i]);
	}
}

void Parser:: setTimeFreq(t_flag_parser *flags, int pos_flag) {
	if (flags->flags[pos_flag].args_count != 1) {
		std::cerr << "server: only 1 time unit divider is allowed" << std::endl;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
	try {
		this->time_freq = std::stoi(flags->flags[pos_flag].args[0]);
	}
	catch (const std::exception &e) {
		std::cerr << "server: invalid time unit divider '" << flags->flags[pos_flag].args[0] << "'" << std::endl;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
	if (this->time_freq < 1 || this->time_freq > 1000) {
		std::cerr << "server: invalid time unit divider '" << flags->flags[pos_flag].args[0] << "' try 1-1000" << std::endl;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
}

void Parser:: setDebug() {
	this->debug = true;
}

void Parser::settersParser(t_flag_parser *flags) {
	if (flags->extra_args_count != 0)
	{
		std::cout << USAGE;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}

	int pos_flag = -1;
	this->debug = false;

	if ((pos_flag = check_flag(flags, 0, "help")) != -1)		{
		std::cout << USAGE;
		cleanup_parser(flags);
		exit(EXIT_SUCCESS);
	} if ((pos_flag = check_flag(flags, 'p', "port")) != -1)	{
		setPort(flags, pos_flag);
	} if ((pos_flag = check_flag(flags, 'x', "width")) != -1)	{
		setWidth(flags, pos_flag);
	} if ((pos_flag = check_flag(flags, 'y', "height")) != -1)	{
		setHeight(flags, pos_flag);
	} if ((pos_flag = check_flag(flags, 'n', "names")) != -1)	{
		setTeams(flags, pos_flag);
	} if ((pos_flag = check_flag(flags, 'c', "clients")) != -1)	{
		setTeamsMembersLimit(flags, pos_flag);
	} if ((pos_flag = check_flag(flags, 't', "time")) != -1)	{
		setTimeFreq(flags, pos_flag);
	} if ((pos_flag = check_flag(flags, 'd', "debug")) != -1)	{
		setDebug();
	}


	if (this->port == -1 ||
		this->x == -1 || this->y == -1 ||
		this->teams_names.empty() ||
		this->teams_members_limit == -1 ||
		this->time_freq == -1
	) {
		std::cerr << "server: missing arguments"<< std::endl;
        dprintf(2, "Try '%s --help' or '%s --usage' for more information.\n", flags->argv[0], flags->argv[0]);
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
}

Parser::Parser(int argc, char **argv) : port(-1), x(-1), y(-1), teams_names(), teams_members_limit(-1), time_freq(-1) {
	t_flag available_flags[] = {
		INIT_FLAG(0,	"help",		NO_ARG,		SINGLE_ARG),
		INIT_FLAG('p',	"port",		NEED_ARG,	SINGLE_ARG),
		INIT_FLAG('x',	"width",	NEED_ARG,	SINGLE_ARG),
		INIT_FLAG('y',	"height",	NEED_ARG,	SINGLE_ARG),
		INIT_FLAG('n',	"names",	NEED_ARG,	MULTIPLE_ARG),
		INIT_FLAG('c',	"clients",	NEED_ARG,	SINGLE_ARG),
		INIT_FLAG('t',	"time",		NEED_ARG,	SINGLE_ARG),
		INIT_FLAG('d',	"debug",	NO_ARG  ,	SINGLE_ARG),
	};

	t_flag_parser flags = parser_init(available_flags, FLAGS_COUNT(available_flags), argc, argv);

	parse(&flags);
	print_parsed_flags(&flags);
	settersParser(&flags);
	cleanup_parser(&flags);
}

Parser::~Parser() {
}

int Parser::getPort(void) const {
	return (this->port);
}

int Parser::getWidth(void) const {
	return (this->x);
}

int Parser::getHeight(void) const {
	return (this->y);
}

int Parser::getTeamsMembersLimit(void) const {
	return (this->teams_members_limit);
}

int Parser::getTimeFreq(void) const {
	return (this->time_freq);
}

t_teams_names Parser::getTeamsNames(void) const {
	return (this->teams_names);
}
