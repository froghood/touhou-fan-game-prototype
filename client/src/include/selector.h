#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <game.h>
#include <character.h>
#include <stage.h>

struct CharacterSelector {
	const std::vector<std::string> characterList{
		"reimu",
		"marisa"
	};

	Character p1Index = Character::Reimu, p2Index = Character::Reimu;
	sf::Uint8 numCharacters = characterList.size();

	bool p1Selected = false;
	bool p2Selected = false;

	bool enabled = false;
	bool visible = false;

	sf::Clock bothSelectedTimer;

	const sf::Uint8 margin = 20;
	const sf::Uint8 characterBoxSize = 100;

	sf::Text text;
	sf::RectangleShape rect;

	void start(Game& game);

	void p1Increment();
	void p2Increment();

	void p1Decrement();
	void p2Decrement();

	void p1Select();
	void p2Select();

	void p1Deselect();
	void p2Deselect();

	bool bothSelected();
	
	void enable();
	void disable();

	void show();
	void hide();
	
	void render(sf::RenderWindow& window);
};

struct StageSelector {
	std::vector<std::string> stageList{
		"stageA",
		"stageB",
		"stageC"
	};

	Stage index = Stage::StageA;
	sf::Uint8 numStages = stageList.size();

	bool selected = false;

	bool enabled = false;
	bool visible = false;

	const float margin = 20;
	const float stageBoxWidth = 150;
	const float stageBoxHeight = 40;

	sf::Text text;
	sf::RectangleShape rect;

	void start(Game& game);

	void increment();
	void decrement();

	void select();

	void enable();
	void disable();

	void show();
	void hide();

	void render(sf::RenderWindow& window);
};