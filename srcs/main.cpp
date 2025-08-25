#include <iostream>
#include "Parser.hpp"
#include "TCPServer.hpp"
#include "Inventory.hpp"
#include "Team.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Utils.hpp"
#include <signal.h>

// ./server -p 8080 -x 10 -y 10 --names hola que tal -c 4 -t 100

void signal_handler(int signum) {
	(void)signum;
}

int main(int argc, char **argv) {
	signal(SIGINT, signal_handler);

	Parser	parser(argc, argv);
	Game	game(&parser);

	TCPServer server(parser.getPort(), game);

	while (!game.get_end()) {
		game.run_tick();
		server.inputOutputComms();
	}
	
	return 0;
}
