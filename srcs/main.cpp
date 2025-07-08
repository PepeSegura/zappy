#include <iostream>
#include "Parser.hpp"
#include "TCPServer.hpp"
#include "Inventory.hpp"
#include "Team.hpp"
#include "Player.hpp"

int main(int argc, char **argv) {
	Parser parser(argc, argv);
	TCPServer server(parser.getPort()); //cambiar de 8080 al puerto
	Team team_a;
	Player player_a;
	Inventory inv_a;
	std::cout << inv_a;

	team_a.addPlayer(&player_a);
	//init gameLogic
	/*while !exit {
		TCPinputOutput
		GameLogic
	}*/
	team_a.removePlayer(&player_a);
	while (true) {
		server.inputOutputComms();
	}
	return 0;
}