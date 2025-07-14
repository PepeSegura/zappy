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
	Game	game(&parser);

	TCPServer server(parser.getPort(), game);

	Player *a = new Player();

	game.add_player_to_team("hola", a);

	a->add_command("dasfas");
	a->add_command("avance");
	a->add_command("droite");
	a->add_command("pose nourriture");
	a->add_command(" ");
	a->add_command("");
	a->add_command("dasfas");
	a->add_command("avance");
	a->add_command("fork");
	a->add_command("broadcast pepepepe");
	a->add_command("avance");

	game.remove_player(a);

	while (true) {
		server.inputOutputComms();
	}
	return 0;
}