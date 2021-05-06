#include <player.h>

void Player::update(double& delta) {
	pos += vel * delta;
}

void Player::render(sf::RenderWindow& window) {
	rect.setPosition(sf::Vector2f(pos.x, pos.y));
	rect.setSize(sf::Vector2f(32, 32));
	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::White);
	rect.setFillColor(sf::Color::Black);
	rect.center();

	window.draw(rect);
}

void Player::actionPressed(Network& network, Game& game, Action& action) {
	network.sendPacket << PacketType::OpponentActionPressed << action;
	network.send();
	sf::Vector2<double> input(
		bool(action == Action::Right) - bool(action == Action::Left),
		bool(action == Action::Down) - bool(action == Action::Up));
	vel += input * unfocusedMovespeed;
}

void Player::actionReleased(Network& network, Game& game, Action& action) {
	network.sendPacket << PacketType::OpponentActionReleased << action;
	network.send();
	sf::Vector2<double> input(
		bool(action == Action::Right) - bool(action == Action::Left),
		bool(action == Action::Down) - bool(action == Action::Up));
	vel -= input * unfocusedMovespeed;
}

//reimu
void PlayerReimu::nonA() {}
void PlayerReimu::nonB() {}
void PlayerReimu::spellA() {}
void PlayerReimu::spellB() {}

//marisa
void PlayerMarisa::nonA() {}
void PlayerMarisa::nonB() {}
void PlayerMarisa::spellA() {}
void PlayerMarisa::spellB() {}