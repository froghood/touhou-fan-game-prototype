#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <console.h>
#include <network.h>
#include <controls.h>

struct Console;
struct Network;
struct State;

struct Game {
	sf::RenderWindow window;
	Controls controls;

	sf::Font font;

	State* state;

	//loop stuff
	sf::Clock clock;
	double previous;
	double current;
	double delta;
	double framerate;

	Game();
	void start(Console& console, Network& network);
	void setState(State* newState);

	void loop(Console& console, Network& network);
	void event(Console& console, Network& network);

	void keyPressed(Console& console, Network& network, sf::Keyboard::Key& key);
	void keyReleased(Console& console, Network& network, sf::Keyboard::Key& key);

	void update(double delta);
	void render(Network& network);

	void updateFramerate(double& current);
};



