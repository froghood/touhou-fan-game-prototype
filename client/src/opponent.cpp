#include <opponent.h>

void Opponent::update(double& delta) {
	pos += vel * delta;
}

void Opponent::render(sf::RenderWindow& window) {
	rect.setPosition(sf::Vector2f(pos.x, pos.y));
	rect.setSize(sf::Vector2f(32, 32));
	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::White);
	rect.setFillColor(sf::Color::Black);
	rect.center();

	window.draw(rect);
}

void Opponent::actionPressed(sf::Packet& packet) {
	Action action;
	packet >> action;
	sf::Vector2<double> input(
		bool(action == Action::Right) - bool(action == Action::Left),
		bool(action == Action::Down) - bool(action == Action::Up));
	vel += input * unfocusedMovespeed;
}

void Opponent::actionReleased(sf::Packet& packet) {
	Action action;
	packet >> action;
	sf::Vector2<double> input(
		bool(action == Action::Right) - bool(action == Action::Left),
		bool(action == Action::Down) - bool(action == Action::Up));
	vel -= input * unfocusedMovespeed;
}

//reimu
void OpponentReimu::nonA() {}
void OpponentReimu::nonB() {}
void OpponentReimu::spellA() {}
void OpponentReimu::spellB() {}

//marisa
void OpponentMarisa::nonA() {}
void OpponentMarisa::nonB() {}
void OpponentMarisa::spellA() {}
void OpponentMarisa::spellB() {}
