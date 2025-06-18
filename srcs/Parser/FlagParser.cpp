#include "FlagParser.hpp"

t_flag_parser	parser_init(t_flag *flags, size_t count, int argc, char **argv)
{
	return (t_flag_parser){
		.flags = flags,
		.count = count,
		.argc = argc,
		.argv = argv,
		.pos = 1,
		.extra_args = NULL,
		.extra_args_count = 0,
	};
}

void	add_arg(t_flag *flag, char *new_arg)
{
	flag->args = (char **)realloc(flag->args, (flag->args_count + 1) * sizeof(char *));
	flag->args[flag->args_count] = new_arg;
	flag->args_count++;
	flag->present++;
}

void	add_extra_arg(t_flag_parser *parser, char *new_extra_arg)
{
	parser->extra_args = (char **)realloc(parser->extra_args, (parser->extra_args_count + 1) * sizeof(char *));
	parser->extra_args[parser->extra_args_count] = new_extra_arg;
	parser->extra_args_count++;
}

int	parse_short_flag_arg(t_flag_parser *parser, t_flag *flag, char *short_flags, int i)
{
	if (flag->has_arg == NO_ARG)
		return (NO_ARG);

	if (short_flags[i + 1] != '\0')
	{
		if (short_flags[i + 1] == '=')
			i++;
		add_arg(flag, &short_flags[i + 1]);
		return (NEED_ARG);
	}

	if (parser->pos + 1 >= parser->argc || parser->argv[parser->pos + 1][0] == '-')
	{
		dprintf(2, "%s: option requires an argument -- '%c'\n", parser->argv[0], flag->short_name);
		dprintf(2, "Try '%s --help' or '%s --usage' for more information.\n", parser->argv[0], parser->argv[0]);
		exit(EXIT_FAILURE);
	}
	parser->pos++;
	add_arg(flag, parser->argv[parser->pos]);
	return (NEED_ARG);
}

t_flag*	match_short_flag(t_flag_parser *parser, char c)
{
	for (size_t i = 0; i < parser->count; i++)
	{
		if (parser->flags[i].short_name == c)
		{
			parser->flags[i].present++;
			return (&parser->flags[i]);
		}
	}
	return (NULL);
}

int	parse_long_flag_arg(t_flag_parser *parser, t_flag *flag, char *new_arg)
{
	if (flag->has_arg == NO_ARG)
		return (NO_ARG);

	if (new_arg)
		return (add_arg(flag, new_arg), NEED_ARG);

	if (parser->pos + 1 >= parser->argc || parser->argv[parser->pos + 1][0] == '-')
	{
		if (flag->long_name)
		{
			dprintf(2, "%s: option '--%s' requires an argument\n", parser->argv[0], flag->long_name);
			dprintf(2, "Try '%s --help' or '%s --usage' for more information.\n", parser->argv[0], parser->argv[0]);
			exit(EXIT_FAILURE);
		}
		if (flag->short_name)
		{
			dprintf(2, "%s: option requires an argument -- '%c'\n", parser->argv[0], flag->short_name);
			dprintf(2, "Try '%s --help' or '%s --usage' for more information.\n", parser->argv[0], parser->argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	parser->pos++;
	add_arg(flag, parser->argv[parser->pos]);
	return (NEED_ARG);
}

t_flag*	match_long_flag(t_flag_parser *parser, const char *name)
{
	char *equal_pos = (char *)strchr(name, '=');
	char *arg = NULL;

	if (equal_pos)
	{
		arg = equal_pos + 1;
		equal_pos[0] = '\0';
	}

	for (size_t i = 0; i < parser->count; i++)
	{
		if (parser->flags[i].long_name && strcmp(parser->flags[i].long_name, name) == 0)
		{
			parser->flags[i].present++;
			parse_long_flag_arg(parser, &parser->flags[i], arg);
			return (&parser->flags[i]);
		}
	}
	return (NULL);
}

void	parse(t_flag_parser *parser)
{
	while (parser->pos < parser->argc)
	{
		char *arg = parser->argv[parser->pos];
		if (strncmp(arg, "--", 2) == 0)
		{
			char *name = arg + 2;
			t_flag *flag = match_long_flag(parser, name);
			if (!flag)
			{
				dprintf(2, "%s: unrecognized option '--%s'\n", parser->argv[0], name);
				dprintf(2, "Try '%s --help' or '%s --usage' for more information.\n", parser->argv[0], parser->argv[0]);
				exit(EXIT_FAILURE);
			}
		}
		else if (arg[0] == '-')
		{
			char *short_flags = arg + 1;
			for (size_t i = 0; short_flags[i] != '\0'; i++)
			{
				t_flag *flag = match_short_flag(parser, short_flags[i]);
				if (!flag)
				{
					dprintf(2, "%s: invalid option -- '%c'\n", parser->argv[0], short_flags[i]);
					dprintf(2, "Try '%s --help' or '%s --usage' for more information.\n", parser->argv[0], parser->argv[0]);
					exit(EXIT_FAILURE);
				}
				if (parse_short_flag_arg(parser, flag, short_flags, i) == NO_ARG)
					continue ;
				break ;
			}
		}
		else
			add_extra_arg(parser, arg);
		parser->pos++;
	}
}

void	print_parsed_flags(t_flag_parser *parser)
{
	printf("Flags found:\n");
	for (size_t i = 0; i < parser->count; i++)
	{
		t_flag *flag = &parser->flags[i];
		if (flag->present)
		{
			printf("  ");
			if (flag->short_name)
				printf("-%c", flag->short_name);
			if (flag->short_name && flag->long_name)
				printf(", ");
			if (flag->long_name)
				printf("--%s", flag->long_name);
			
			if (flag->has_arg && flag->args)
			{
				printf(" (args: ");
				for (size_t i = 0; i < flag->args_count; i++)
					printf(" '%s'", flag->args[i]);
				printf(" )");
			}
			printf("\n");
		}
	}

	if (parser->extra_args_count != 0)
	{
		printf("Extra params: (");
		for (size_t i = 0; i < parser->extra_args_count; i++)
			printf(" '%s'", parser->extra_args[i]);
		printf(" )\n");
	}
}

void	cleanup_parser(t_flag_parser *parser)
{
	if (parser->extra_args_count != 0)
		free(parser->extra_args);
	for (size_t i = 0; i < parser->count; i++)
	{
		if (parser->flags[i].args_count != 0)
			free(parser->flags[i].args);
	}
}

int	check_short_flag(t_flag_parser *parser, char short_flag)
{
	for (size_t i = 0; i < parser->count; i++)
	{
		if (parser->flags[i].short_name == short_flag && parser->flags[i].present)
			return (i);
	}
	return (-1);
}

int	check_long_flag(t_flag_parser *parser, char *long_flag)
{
	for (size_t i = 0; i < parser->count; i++)
	{
		if (strcmp(parser->flags[i].long_name, long_flag) == 0 && parser->flags[i].present)
			return (i);
	}
	return (-1);
}

int check_flag(t_flag_parser *parser, char short_flag, char *long_flag)
{
	int	flag_pos = -1;

	if (short_flag != 0)
		flag_pos = check_short_flag(parser, short_flag);
	if (long_flag != NULL)
		flag_pos = check_long_flag(parser, long_flag);
	return (flag_pos);
}
