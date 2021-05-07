#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <vector>

#include <entity.h>
#include <player.h>
#include <opponent.h>
#include <selector.h>

struct State {
	//shared by all derived classes

	sf::Text text;

	virtual void start(Game& game) = 0;
	virtual void update(double& delta) = 0;
	virtual void render(sf::RenderWindow& window, Network& network) = 0;
	virtual void playerActionPressed(Console& console, Network& network, Game& game, Action& action) = 0;
	virtual void playerActionReleased(Console& console, Network& network, Game& game, Action& action) = 0;
	virtual void opponentActionPressed(Console& console, sf::Packet& packet) = 0;
	virtual void opponentActionReleased(sf::Packet& packet) = 0;

	//character select state

	//match state
	virtual void opponentVelocityChange(Network& network, sf::Packet& packet);
	virtual void opponentGraze(sf::Packet& packet);
	virtual void opponentHit(sf::Packet& packet);
};

struct CharacterSelectState : State {
	CharacterSelector characterSelector;
	StageSelector stageSelector;
	bool characterSelected = false;
	bool opponentCharacterSelectStateed = false;

	CharacterSelectState();
	void start(Game& game) override;

	void playerActionPressed(Console& console, Network& network, Game& game, Action& action) override;
	void playerActionReleased(Console& console, Network& network, Game& game, Action& action) override;
	void update(double& delta) override;
	void render(sf::RenderWindow& window, Network& network) override;

	void opponentActionPressed(Console& console, sf::Packet& packet) override;
	void opponentActionReleased(sf::Packet& packet) override;
};

struct MatchState : State {
	Player* player;
	Opponent* opponent;
	std::vector<Entity> entityList;

	sf::Uint64 startTimestamp;

	MatchState(sf::Uint8 player, sf::Uint64& timestamp, Character& p1, Character& p2, Stage& stage);
	void start(Game& game) override;

	void playerActionPressed(Console& console, Network& network, Game& game, Action& action) override;
	void playerActionReleased(Console& console, Network& network, Game& game, Action& action) override;
	void update(double& delta) override;
	void render(sf::RenderWindow& window, Network& network) override;

	void opponentActionPressed(Console& console, sf::Packet& packet) override;
	void opponentActionReleased(sf::Packet& packet) override;
	void opponentVelocityChange(Network& network, sf::Packet& packet) override;
	void opponentGraze(sf::Packet& packet) override;
	void opponentHit(sf::Packet& packet) override;
};