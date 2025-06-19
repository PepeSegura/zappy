#pragma once

# include <sys/poll.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <cstdio>
# include <vector>
# include <utility>
# include <cstdlib>
# include <cstring>
# include <iostream>

# define MAX_CLIENTS 1024

typedef std::vector<pollfd>::iterator	poll_iterator;

class TCPServer {
	private:
		int					socketFd;
		struct sockaddr_in	server_addr;
		std::vector<pollfd>	pollFds;

		void	acceptClient();
		void	readClientData(size_t *idx);
		void	disconnectClient(size_t *idx);
		void	createBindSocket(int port);
		void	addToPoll(int fd, int flags);

	public:
		TCPServer(int port);
		~TCPServer();
		
		void 	inputOutputComms();
};