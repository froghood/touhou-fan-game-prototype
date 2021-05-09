#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


struct Entity {
	sf::Vector2<double> position;
	sf::Vector2<double> velocity;

	Entity(double x, double y) : position(x, y), velocity(0, 0) {}

	virtual void update(double& delta) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};