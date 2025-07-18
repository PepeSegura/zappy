#include <iostream>
#include "Parser.hpp"
#include "TCPServer.hpp"
#include "Inventory.hpp"
#include "Team.hpp"
#include "Player.hpp"
#include "Game.hpp"

// ./server -p 8080 -x 10 -y 10 --names hola que tal -c 4 -t 100

int main(int argc, char **argv) {
	Parser	parser(argc, argv);
	Game	game(&parser);

	TCPServer server(parser.getPort(), game);

	while (!game.get_end()) {
		server.inputOutputComms();
		game.run_tick();
	}
	
	return 0;
}