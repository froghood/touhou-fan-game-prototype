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
	sf::Vector2<sf::Int8> input(
		(action == Action::Right) - (action == Action::Left),
		(action == Action::Down) - (action == Action::Up));
	double dirAngle = atan2(input.y, input.x);
	addVelocity(network, sf::Vector2<double>(
		input.x * unfocusedMovespeed * abs(cos(dirAngle)),
		input.y * unfocusedMovespeed * abs(sin(dirAngle))));
}

void Player::actionReleased(Network& network, Game& game, Action& action) {
	sf::Vector2<sf::Int8> input(
		(action == Action::Right) - (action == Action::Left),
		(action == Action::Down) - (action == Action::Up));
	double dirAngle = atan2(input.y, input.x);
	subVelocity(network, sf::Vector2<double>(
		input.x * unfocusedMovespeed * abs(cos(dirAngle)),
		input.y * unfocusedMovespeed * abs(sin(dirAngle))));
}

void Player::addVelocity(Network& network, sf::Vector2<double> v) {
	vel += v;
	network.sendPacket << PacketType::OpponentVelocityChange << network.getTimestamp() << pos << vel;
	network.send();
}

void Player::subVelocity(Network& network, sf::Vector2<double> v) {
	vel -= v;
	network.sendPacket << PacketType::OpponentVelocityChange << network.getTimestamp() << pos << vel;
	network.send();
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

