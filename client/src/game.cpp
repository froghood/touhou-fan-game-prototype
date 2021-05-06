#include <game.h>
#include <state.h>
#include <fstream>

Game::Game() : state(nullptr), previous(0), current(0), delta(0), framerate(0) {}

void Game::start(Console& console, Network& network) {
	std::cout << "loading game...\r";
	window.create(sf::VideoMode(1280, 720), console.isHosting ? "host" : "client");
	window.setKeyRepeatEnabled(false);

	if (!font.loadFromFile("src/fonts/arial.ttf")) { std::string error; throw error; }

	controls.start();

	setState(new CharacterSelectState);

	if (console.isHosting) {
		network.sendPacket << PacketType::SyncStart << network.getTimestamp();
		network.send();
	}

	std::cout << "game loaded               \n";
	try { loop(console, network); }
	catch (std::string& error) { throw error; }
}

void Game::loop(Console& console, Network& network) {
	while (window.isOpen()) {
		current = clock.getElapsedTime().asSeconds();
		delta = current - previous;
		std::cout << delta << "\n";
		framerate = 1 / delta;

		try { network.receive(console, *this); }
		catch (std::string& error) { throw error; }

		event(console, network);
		update(delta / 1);
		render(network);

		previous = current;
	}
}

void Game::event(Console& console, Network& network) {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				keyPressed(console, network, event.key.code);
				break;
			case sf::Event::KeyReleased:
				keyReleased(console, network, event.key.code);
				break;
			default:
				break;
		}
	}
}

void Game::keyPressed(Console& console, Network& network, sf::Keyboard::Key& key) {
	state->playerActionPressed(console, network, *this, controls.getAction(key));
}

void Game::keyReleased(Console& console, Network& network, sf::Keyboard::Key& key) {
	state->playerActionReleased(console, network, *this, controls.getAction(key));
}


void Game::setState(State* newState) {
	if (state != nullptr) delete state;
	state = newState;
	state->start(*this);
}

void Game::update(double delta) {
	std::cout << delta << "\n";
	state->update(delta);
}

void Game::render(Network& network) {
	window.clear(sf::Color(30,35,45));
	state->render(window, network);
	window.display();
}

void Game::updateFramerate(double& current) {
	static double previous = 0;
	double delta = current - previous;
	framerate = 1 / delta;
	previous = current;
}
