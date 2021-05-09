#include <opponent.h>

template <typename T>
inline T sign(T n) {
	return (n > 0) - (n < 0);
}

void Opponent::update(double& delta) {
	position += velocity * delta;
	smoothPosition *= pow(0.0018, delta);
}

void Opponent::render(sf::RenderWindow& window) {

	rect.setPosition(sf::Vector2f(position.x + smoothPosition.x, position.y + smoothPosition.y));
	//rect.setPosition(sf::Vector2f(position.x, position.y));
	rect.setSize(sf::Vector2f(32, 32));
	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::White);
	rect.setFillColor(sf::Color::Black);
	rect.center();
	window.draw(rect);

	/*rect.setPosition(sf::Vector2f(position.x + smoothPosition.x, position.y + smoothPosition.y));
	rect.setSize(sf::Vector2f(16, 16));
	rect.setFillColor(sf::Color::Red);
	rect.center();
	window.draw(rect);*/
}

void Opponent::actionPressed(sf::Packet& packet) {}
void Opponent::actionReleased(sf::Packet& packet) {}

void Opponent::velocityChange(Network& network, sf::Packet& packet) {
	sf::Vector2<double> oldPosition = position;
	sf::Uint64 timestamp;
	packet >> timestamp >> position >> velocity;
	position += velocity * network.getLatency(timestamp);
	oldPosition -= position;
	smoothPosition += oldPosition;
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


