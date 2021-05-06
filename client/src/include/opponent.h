#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include <entity.h>
#include <game.h>

struct Opponent : Entity {
	const double unfocusedMovespeed, focusedMovespeed;

	sf::RectangleShape rect;

	Opponent(double x, double y, double m, double fm)
		: Entity(x, y)
		, unfocusedMovespeed(m)
		, focusedMovespeed(fm) {
	}

	void update(double& delta) override;
	void render(sf::RenderWindow&) override;
	void actionPressed(sf::Packet& packet);
	void actionReleased(sf::Packet& packet);

	virtual void nonA() = 0;
	virtual void nonB() = 0;
	virtual void spellA() = 0;
	virtual void spellB() = 0;
};

struct OpponentReimu : Opponent {
	sf::Uint16 unfocusedMovespeed = 180;
	sf::Uint16 focusedMovespeed = 90;

	OpponentReimu(sf::Uint16 x, sf::Uint16 y) : Opponent(x, y, 160, 100) {}

	void nonA() override;
	void nonB() override;
	void spellA() override;
	void spellB() override;
};

struct OpponentMarisa : Opponent {
	OpponentMarisa(sf::Uint16 x, sf::Uint16 y) : Opponent(x, y, 200, 120) {}

	void nonA() override;
	void nonB() override;
	void spellA() override;
	void spellB() override;
};