#pragma once

# include <iostream>
# include <deque>
# include <map>

# include "Messages.hpp"
# include "Inventory.hpp"

class Inventory;

struct Command_Data {
	Command		cmd;
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
		std::string team_name;
		Inventory	inv;
		int			level;
		uint8_t		dir; // N, S, W, E
		int			x;
		int			y;
		bool		dead;
		bool		handshake_finished;

		int			sock_fd;
		int			state;
		std::string	send_buffer;
		std::string msg_to_parse;
		std::string	recv_buffer;

		std::deque<Command_Data> command_queue;

		int64_t		last_action_start_time;

	public:
		Player();
		Player(std::string);
		~Player();

		Player&  operator=(const Player &other);

		void		add_buffer_or_parse_msg(std::string);
		void		parse_msg(void);

		std::string	get_team_name() const;
		Inventory&	get_inv();
		int			get_level() const;
		int			get_x() const;
		int			get_y() const;
		int			get_sock_fd() const;
		int			get_state() const;
		std::string	get_recv_buffer() const;
		std::string	get_send_buffer() const;
		bool		get_handshake() const;
		int64_t		get_last_start_time() const;

		void		set_level(int);
		void		set_x(int);
		void		set_y(int);
		void		set_sock_fd(int);
		void		set_state(int);
		void		set_recv_buffer(std::string &);
		void		set_send_buffer(std::string &);
		void		set_team_name(std::string &);
		void		set_handshake(bool &);
		void		add_command(std::string);
		void		set_last_start_time(int64_t);

		bool			has_queued_actions() const;
		Command_Data	get_current_command() const;

		void		Eat();
		void		Avance();
		void		Droite();
		void		Gauche();
		std::string	Inventaire();
		void		Prend(std::string item);
		void		Pose(std::string item);
		void		IncantationBgn();
		void		IncantationEnd();
};
