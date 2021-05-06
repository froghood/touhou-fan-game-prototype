#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


struct Entity {
	sf::Vector2<double> pos;
	sf::Vector2<double> vel;

	Entity(double x, double y) : pos(x, y), vel(0, 0) {}

	virtual void update(double& delta) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};