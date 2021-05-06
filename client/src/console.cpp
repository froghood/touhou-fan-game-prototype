#include "console.h"

Console::Console() : isHosting(false), port(0) {
	std::cout << "console loaded...\n";
}

void Console::start(bool useDefault) {
	askName();
	askIsHosting();
	if (useDefault) {
		address = "98.231.120.217";
		port = 25565;
		//std::cout << "using default address and port\n";
	} else {
		if (!isHosting) askAddress();
		askPort();
	}
}

void Console::askName() {
	std::cout << "name?\n";
	std::cin >> name;
	std::cout << "\n";
}

void Console::askIsHosting() {
	std::cout << "hosting? ('y' = yes, 'n' = no)\n";
	char answer;
	std::cin >> answer;
	std::cout << "\n";

	if (answer == 'y') {
		isHosting = true;
	} else if (answer != 'n') {
		std::cout << "unrecognized answer, try again\n";
		askIsHosting();
	}	
}

void Console::askAddress() {
	std::cout << "address? (no port)\n";
	std::cin >> address;
	std::cout << "\n";
}

void Console::askPort() {
	std::cout << "port?\n";
	std::cin >> port;
	std::cout << "\n";
}
