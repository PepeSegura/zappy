#pragma once

# include <iostream>
# include <deque>
# include <map>
# include <chrono>

# include "Messages.hpp"
# include "Inventory.hpp"
# include "Incantation.hpp"

class Game;
class Inventory;
class Incantation;

typedef std::chrono::high_resolution_clock::time_point timePoint;

# define FOOD_TICKS 126
# define EGG_HATCH_TICKS 600
# define QUEUE_SIZE 10
# define QUEUE_SIZE_DBG 200
# define QUEUE_SIZE_GRAPHIC 1024

struct Command_Data {
	Command		cmd;
	std::string	cmd_name;
	std::string	args;
};

enum Player_States {
	Handshake,
	Free,
	ExecutingAction
};


class Player
{
	private:
		bool		graphic_client;
		Game*		game_ptr;
		std::string team_name;
		Inventory	inv;
		int			level;
		uint8_t		dir; // N, S, W, E
		int			x;
		int			y;
		bool		was_forked;
		bool		dead, already_hatched;
		bool		handshake_finished;
		bool		is_disconnected, is_encantating, encantation_prechecked;

		int			sock_fd, id;
		int			state;
		std::string	send_buffer;
		std::string msg_to_parse;
		std::string	recv_buffer;

		std::deque<Command_Data> command_queue;

		timePoint		last_action_start_time, egg_creation, incantationStartTime;
		int64_t		ticks_until_eat;

	public:
		//Player();
		Player(std::string, timePoint, Game *, int id);
		Player(Game*);
		~Player();

		Player&  operator=(const Player &other);

		void		add_buffer_or_parse_msg(std::string);
		void		parse_msg(void);

		bool		is_graphic_client() const;
		std::string	get_team_name() const;
		Inventory&	get_inv();
		int			get_level() const;
		uint8_t		get_dir() const;
		int			get_x() const;
		int			get_y() const;
		int			get_sock_fd() const;
		int			get_state() const;
		std::string	get_recv_buffer() const;
		std::string	get_send_buffer() const;
		bool		get_handshake() const;
		timePoint		get_last_start_time() const;
		timePoint		getIncantationStartTime() const { return incantationStartTime ; }
		bool		get_disconnected() const;
		bool		get_encantation_precheck() const;
		bool		get_is_encantating() const;
		bool		get_dead() const;
		bool		get_was_forked() const;
		bool		get_already_hatched() const;
		int			get_id() const;
		bool		is_hatched() const;

		void		set_graphic_client(bool);
		void		set_level(int);
		void		set_x(int);
		void		set_y(int);
		void		set_sock_fd(int);
		void		set_state(int);
		void		set_recv_buffer(std::string &);
		void		clear_send_buffer(void);
		void		set_send_buffer(std::string);
		void		set_team_name(std::string &);
		void		set_handshake(bool);
		void		add_command(std::string);
		void		set_last_start_time(timePoint);
		void		setIncantationStartTime(timePoint start) { this->incantationStartTime = start; }
		void		set_disconnect(bool);
		void		set_encantation_precheck(bool);
		void		set_dead(bool);
		void		set_already_hatched(bool);
		void		set_was_forked(bool);

		bool			has_queued_actions() const;
		Command_Data	get_current_command() const;
		void			pop_command();
		void			pop_all_commands();

		void		Eat();
		void		Avance();
		void		Droite();
		void		Gauche();
		std::string	Inventaire();
		void		Prend(std::string item);
		void		Pose(std::string item);
		void		IncantationBgn(Incantation &);
		void		IncantationStart();
		void		IncantationEnd();
		void		handshake(Player *);

		void		check_hatch_and_eat();
		Incantation *incantation;
		bool		incantationFailed, firstPrecheck, handshakeNotified;
};
