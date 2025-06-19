#include <iostream>
#include "Parser.hpp"
#include "TCPServer.hpp"

int main(int argc, char **argv) {
	Parser parser(argc, argv);
	TCPServer server(parser.getPort()); //cambiar de 8080 al puerto
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