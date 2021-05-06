#include <state.h>

MatchState::MatchState(sf::Uint8 playerSide, sf::Uint64& timestamp, Character& p1, Character& p2, Stage& stage)
	: player(nullptr), opponent(nullptr), startTimestamp(timestamp + 3000000) {
	switch (playerSide) {
		case 1:
			switch (p1) {
				case Character::Reimu: player = new PlayerReimu(sf::Uint16(360), sf::Uint16(360)); break;
				case Character::Marisa: player = new PlayerMarisa(sf::Uint16(360), sf::Uint16(360)); break;
			}

			switch (p2) {
				case Character::Reimu: opponent = new OpponentReimu(sf::Uint16(920), sf::Uint16(360)); break;
				case Character::Marisa: opponent = new OpponentMarisa(sf::Uint16(920), sf::Uint16(360)); break;
			}
			break;
		case 2:
			switch (p1) {
				case Character::Reimu: opponent = new OpponentReimu(sf::Uint16(360), sf::Uint16(360)); break;
				case Character::Marisa: opponent = new OpponentMarisa(sf::Uint16(360), sf::Uint16(360)); break;
			}

			switch (p2) {
				case Character::Reimu: player = new PlayerReimu(sf::Uint16(920), sf::Uint16(360)); break;
				case Character::Marisa: player = new PlayerMarisa(sf::Uint16(920), sf::Uint16(360)); break;
			}
			break;
	}
}

void MatchState::start(Game& game) {}

void MatchState::playerActionPressed(Console& console, Network& network, Game& game, Action& action) {
	player->actionPressed(network, game, action);
}

void MatchState::playerActionReleased(Console& console, Network& network, Game& game, Action& action) {
	player->actionReleased(network, game, action);
}

void MatchState::opponentActionPressed(Console& console, sf::Packet& packet) {
	opponent->actionPressed(packet);
}

void MatchState::opponentActionReleased(sf::Packet& packet) {
	opponent->actionReleased(packet);
}

void MatchState::update(double& delta) {
	player->update(delta);
	opponent->update(delta);
}
void MatchState::render(sf::RenderWindow& window, Network& network) {
	player->render(window);
	opponent->render(window);
}

void MatchState::opponentGraze(sf::Packet& packet) {}
void MatchState::opponentHit(sf::Packet& packet) {}