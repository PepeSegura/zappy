#include "Parser.hpp"

// #include "FlagParser.hpp"


void Parser::settersParser(t_flag_parser *flags)
{
	int pos_flag = -1;

	if 	 ((pos_flag = check_flag(flags, 0, "help")) != -1)		{
		std::cout << USAGE << std::endl;
		cleanup_parser(flags);
		exit(EXIT_SUCCESS);
	} if ((pos_flag = check_flag(flags, 'p', "port")) != -1)	{
		this->port = std::atoi(flags->flags[pos_flag].args[0]);
		if (this->port <= 0)
		{
			dprintf(2, "server: invalid port '%s'\n", flags->flags[pos_flag].args[0]);
			cleanup_parser(flags);
			exit(EXIT_FAILURE);
		}
	} if ((pos_flag = check_flag(flags, 'x', "width")) != -1)	{
		this->x = std::atoi(flags->flags[pos_flag].args[0]);
	} if ((pos_flag = check_flag(flags, 'y', "height")) != -1)	{
		this->y = std::atoi(flags->flags[pos_flag].args[0]);
	} if ((pos_flag = check_flag(flags, 'n', "names")) != -1)	{
		int count = flags->flags[pos_flag].args_count;
		for (int i = 0; i < count; i++)
			this->teams_names.push_back(flags->flags[pos_flag].args[i]);
	} if ((pos_flag = check_flag(flags, 'c', "clients")) != -1){
		this->authorized_clients = std::atoi(flags->flags[pos_flag].args[0]);
	} if ((pos_flag = check_flag(flags, 't', "time")) != -1)	{
		this->time_div = std::atoi(flags->flags[pos_flag].args[0]);
	}

	if (flags->extra_args_count != 0)
	{
		std::cout << USAGE << std::endl;
		cleanup_parser(flags);
		exit(EXIT_FAILURE);
	}
}

Parser::Parser(int argc, char **argv) : port(-1), x(-1), y(-1), authorized_clients(-1), time_div(-1) {
	std::cout << "Init parser\n";

	t_flag available_flags[] = {
		INIT_FLAG(0,	"help",		NO_ARG,		SINGLE_ARG),
		INIT_FLAG('p',	"port",		NEED_ARG,	SINGLE_ARG),
		INIT_FLAG('x',	"width",	NEED_ARG,	SINGLE_ARG),
		INIT_FLAG('y',	"height",	NEED_ARG,	SINGLE_ARG),
		INIT_FLAG('n',	"names",	NEED_ARG,	MULTIPLE_ARG),
		INIT_FLAG('c',	"clients",	NEED_ARG,	SINGLE_ARG),
		INIT_FLAG('t',	"time",		NEED_ARG,	SINGLE_ARG),
	};

	t_flag_parser flags = parser_init(available_flags, FLAGS_COUNT(available_flags), argc, argv);
	parse(&flags);
	print_parsed_flags(&flags);

	settersParser(&flags);

	cleanup_parser(&flags);

	std::cout << "Port:    " << this->port << std::endl;
	std::cout << "Size:    X:" << this->x << " Y:" << this->y <<std::endl;
	std::cout << "Players: " << this->authorized_clients << std::endl;
	std::cout << "TimeDiv: " << this->time_div << std::endl;
	for (size_t pos = 0; pos < this->teams_names.size(); pos++)
		std::cout << "Team["<< pos <<"]: "<< this->teams_names[pos] << std::endl;
}

Parser::~Parser() {
	std::cout << "Closing parser\n";
}
