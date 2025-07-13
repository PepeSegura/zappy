#include <iostream>
#include "Parser.hpp"
#include "TCPServer.hpp"
#include "Inventory.hpp"
#include "Team.hpp"
#include "Player.hpp"
#include "Game.hpp"

// ./server -p 8080 -x 10 -y 10 --names hola que tal -c 4 -t 100

int main(int argc, char **argv) {
	Parser parser(argc, argv);
	TCPServer server(parser.getPort());

	Game	game(&parser);

	Player a;

	game.add_player("hola", &a);

	game.remove_player(&a);

	while (true) {
		server.inputOutputComms();
	}
	return 0;
}