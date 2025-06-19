#include <iostream>
#include "TCPServer/TCPServer.hpp"

int main(int argc, char **argv) {
	(void) argc;
	(void) argv;
	//parser
	//create tcpsocket-poll
	TCPServer server(8080); //cambiar de 8080 al puerto
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