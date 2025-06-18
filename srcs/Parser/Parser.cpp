#include "Parser.hpp"

#include "FlagParser.hpp"

Parser::Parser(int argc, char **argv) {
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
	cleanup_parser(&flags);
}

Parser::~Parser() {
	std::cout << "Closing parser\n";
}
