#include <iostream>
#include "Parser.hpp"
#include "TCPServer.hpp"
#include "Inventory.hpp"

int main(int argc, char **argv) {
	Parser parser(argc, argv);
	TCPServer server(parser.getPort()); //cambiar de 8080 al puerto
	Inventory a;
	std::cout << a;
	//init gameLogic
	/*while !exit {
		TCPinputOutput
		GameLogic
	}*/
	while (true) {
		server.inputOutputComms();
	}
	return 0;
}