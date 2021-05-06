#include <console.h>
#include <network.h>
#include <game.h>

int main() {
	Console console;
	Network network;
	Game game;

	

	try {
		console.start(true);
		network.start(console, game);
		std::cout << "starting game...\n";
		game.start(console, network);
	}

	catch (std::string& error) {
		std::cout << error << ", closing...\n";
		sf::sleep(sf::seconds(3));
		return 0;
	}	
}