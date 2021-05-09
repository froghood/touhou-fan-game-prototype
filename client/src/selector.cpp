#include <selector.h>

void CharacterSelector::start(Game& game) {
	text.setFont(game.font);
	text.setStyle(sf::Text::Style::Bold);
	text.setOutlineColor(sf::Color::Transparent);
}

void CharacterSelector::p1Increment() { p1Index = Character((sf::Uint8(p1Index) + 1) % numCharacters); }
void CharacterSelector::p2Increment() { p2Index = Character((sf::Uint8(p2Index) + 1) % numCharacters); }


void CharacterSelector::p1Decrement() {
	p1Index = Character((sf::Uint8(p1Index) + characterList.size() - 1) % numCharacters);
}

void CharacterSelector::p2Decrement() {
	p2Index = Character((sf::Uint8(p2Index) + characterList.size() - 1) % numCharacters);
}


void CharacterSelector::p1Select() { p1Selected = true; bothSelectedTimer.restart(); }
void CharacterSelector::p2Select() { p2Selected = true; bothSelectedTimer.restart(); }


void CharacterSelector::p1Deselect() { p1Selected = false; }
void CharacterSelector::p2Deselect() { p2Selected = false; }


bool CharacterSelector::bothSelected() { return p1Selected && p2Selected; }


void CharacterSelector::enable() { enabled = true; }
void CharacterSelector::disable() { enabled = false; }

void CharacterSelector::show() { visible = true; }
void CharacterSelector::hide() { visible = false; }

void CharacterSelector::render(sf::RenderWindow& window) {
	if (visible) {
		auto windowSize = window.getSize();
		auto spacing = characterBoxSize + margin;
		auto offset = spacing * (characterList.size() - 1) / 2;

		//draw header
		text.setString("select your touhou !!");
		text.setFillColor(sf::Color::White);
		text.setPosition(sf::Vector2f(windowSize.x / 2, 60));
		text.setCharacterSize(48);
		text.center();
		window.draw(text);

		//render character boxes and names
		rect.setSize(sf::Vector2f(characterBoxSize, characterBoxSize));
		rect.setOutlineThickness(2);
		rect.setOutlineColor(sf::Color::White);
		rect.setFillColor(sf::Color::Black);
		text.setCharacterSize(16);
		for (sf::Uint8 i = 0; i < characterList.size(); i++) {
			sf::Vector2f positionition(windowSize.x / 2 + spacing * i - offset, windowSize.y / 2);

			rect.setPosition(positionition);
			rect.center();

			text.setPosition(positionition);
			text.setString(characterList[i]);
			text.center();

			window.draw(rect);
			window.draw(text);
		}

		//draw both p1 selector positionitions
		text.setString("P1");
		text.setFillColor(sf::Color(255, 0, 100));
		text.setPosition(sf::Vector2f(
			windowSize.x / 2 + spacing * sf::Uint8(p1Index) - offset,
			windowSize.y / 2 - 70 + 40 * p1Selected));
		text.setCharacterSize(24);
		text.center();
		window.draw(text);

		text.setString("P2");
		text.setFillColor(sf::Color(0, 200, 255));
		text.setPosition(sf::Vector2f(
			windowSize.x / 2 + spacing * sf::Uint8(p2Index) - offset,
			windowSize.y / 2 + 70 - 40 * p2Selected));
		text.setCharacterSize(24);
		text.center();
		window.draw(text);

		//draw timer when both p1s have selected
		if (bothSelected()) {
			float time = bothSelectedTimer.getElapsedTime().asSeconds();
			std::string timeString = std::to_string(std::max(0.f, 3.f - time));
			timeString = timeString.substr(0, timeString.find(".") + 3);

			text.setString(timeString);
			text.setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 200));
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(32);
			text.center();
			window.draw(text);
		}
	}
}

//----------stage----------------------------

void StageSelector::start(Game& game) {
	text.setFont(game.font);
	text.setStyle(sf::Text::Style::Bold);
	text.setOutlineColor(sf::Color::Transparent);
}

void StageSelector::increment() { index = Stage((sf::Uint8(index) + numStages + 1) % numStages); }
void StageSelector::decrement() { index = Stage((sf::Uint8(index) + numStages - 1) % numStages); }

void StageSelector::enable() { enabled = true; }
void StageSelector::disable() { enabled = false; }

void StageSelector::show() { visible = true; }
void StageSelector::hide() { visible = false; }

void StageSelector::select() { selected = true; }

void StageSelector::render(sf::RenderWindow& window) {
	if (visible) {
		auto windowSize = window.getSize();
		auto spacing = stageBoxHeight + margin;
		auto offset = spacing * (stageList.size() - 1) / 2;

		//draw header
		text.setString("omg select the stage !!!");
		text.setCharacterSize(48);
		text.setFillColor(sf::Color::White);
		text.setPosition(sf::Vector2f(windowSize.x / 2, 60.f));
		text.center();
		window.draw(text);

		//draw stage boxes
		rect.setSize(sf::Vector2f(stageBoxWidth, stageBoxHeight));
		rect.setOutlineColor(sf::Color::White);
		rect.setOutlineThickness(2);
		rect.setFillColor(sf::Color::Black);
		text.setCharacterSize(16);
		for (sf::Uint8 i = 0; i < stageList.size(); i++) {
			sf::Vector2f positionition(windowSize.x / 2, windowSize.y / 2 + spacing * i - offset);

			rect.setPosition(positionition);
			rect.center();

			text.setPosition(positionition);
			text.setString(stageList[i]);
			text.center();

			window.draw(rect);
			window.draw(text);
		}

		//draw index positionition
		text.setString("P1");
		text.setFillColor(sf::Color(255, 0, 100));
		text.setCharacterSize(24);
		text.setPosition(sf::Vector2f(
			windowSize.x / 2 - stageBoxWidth / 2 - margin * 1.5,
			windowSize.y / 2 + spacing * sf::Uint8(index) - offset));
		text.center();
		window.draw(text);
	}
}
