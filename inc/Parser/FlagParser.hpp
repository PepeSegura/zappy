#pragma once

# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define NEED_ARG 1
# define NO_ARG 0
# define MULTIPLE_ARG 1
# define SINGLE_ARG 0

typedef struct
{
	char		short_name;	// Short flag (e.g., 'v' for -v)
	const char	*long_name;	// Long flag (e.g., "verbose" for --verbose)
	int			has_arg;	// 1 if the flag expects an argument (e.g., -o file/-ofile/-o=file)
	int			multiple_args;

	char		**args;		// Args found if there is more than one flag with arg
	size_t		args_count;

	int			present;	// 1 if the flag is in the command line
}	t_flag;

typedef struct
{
	t_flag	*flags;			// Array of Flag definitions
	size_t	count;			// Number of flags in the array
	int		argc;			// Original argc
	char	**argv;			// Original argv
	int		pos;			// Current position in argv (during parsing)

	char	**extra_args;	// Extra args that are not a flag or a flag argument
	size_t	extra_args_count;
}	t_flag_parser;

# define FLAGS_COUNT(flags) sizeof(flags) / sizeof(t_flag)
# define INIT_FLAG(short_name, long_name, has_arg, multiple_args) {short_name, long_name, has_arg, multiple_args, NULL, 0, 0}

t_flag_parser	parser_init(t_flag *flags, size_t count, int argc, char **argv);
void			parse(t_flag_parser *parser);
void			print_parsed_flags(t_flag_parser *parser);
void			cleanup_parser(t_flag_parser *parser);

int				check_short_flag(t_flag_parser *parser, char short_flag);
int				check_long_flag(t_flag_parser *parser, char *long_flag);
int				check_flag(t_flag_parser *parser, char short_flag, char *long_flag);
