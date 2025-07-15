#pragma once

# include <iostream>
# include <deque>

# include "Messages.hpp"
# include "Inventory.hpp"

class Inventory;

struct Command_Data {
	Command		cmd;
	std::string	args;
};

class Player
{
	private:
		std::string team_name;
		Inventory	inv;
		int			level;
		int			x;
		int			y;
		bool		handshake_finished;

		int			sock_fd;
		int			state;
		std::string	send_buffer;
		std::string	recv_buffer;

		std::deque<Command_Data> command_queue;

	public:
		Player();
		Player(std::string);
		~Player();

		Player&  operator=(const Player &other);

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
};
