#pragma once

#include <SFML/Config.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <entity.h>
#include <game.h>

struct Player : Entity {

	const double unfocusedMovespeed, focusedMovespeed;
	sf::RectangleShape rect;

	Player(double x, double y, double m, double fm)
		: Entity(x, y)
		, unfocusedMovespeed(m)
		, focusedMovespeed(fm) {
	}

	void update(double& delta) override;
	void render(sf::RenderWindow& window) override;
	void actionPressed(Network& network, Game& game, Action& action);
	void actionReleased(Network& network, Game& game, Action& action);

	void addVelocity(Network& network, sf::Vector2<double> v);
	void subVelocity(Network& network, sf::Vector2<double> v);

	virtual void nonA() = 0;
	virtual void nonB() = 0;
	virtual void spellA() = 0;
	virtual void spellB() = 0;
};

struct PlayerReimu : Player {
	PlayerReimu(sf::Uint16 x, sf::Uint16 y) : Player(x, y, 160, 100) {}

	void nonA() override;
	void nonB() override;
	void spellA() override;
	void spellB() override;
};

struct PlayerMarisa : Player {
	PlayerMarisa(sf::Uint16 x, sf::Uint16 y) : Player(x, y, 200, 120) {}

	void nonA() override;
	void nonB() override;
	void spellA() override;
	void spellB() override;
};