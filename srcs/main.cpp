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

/* 	std::cout << "setting player\n";
	Player *a = new Player(&game);
	std::cout << "after setting player\n";

	Inventory &inv = a->get_inv();

	inv.add_deraumere(10);
	inv.add_nourriture(1);
	inv.add_sibur(2);
	inv.add_linemate(-2);

	std::cout << a->Inventaire() << std::endl;
	game.add_player_to_team("hola", a);

	game.remove_player(a); */

	while (!game.get_end()) {
		server.inputOutputComms();
		game.run_tick();
	}
	
	return 0;
}