#include <state.h>

CharacterSelectState::CharacterSelectState() {}

void CharacterSelectState::start(Game& game) {
	characterSelector.start(game);
	stageSelector.start(game);

	characterSelector.enable();
	characterSelector.show();
}

void CharacterSelectState::playerActionPressed(Console& console, Network& network, Game& game, Action& action) {
	if (characterSelector.enabled) {
		switch (console.isHosting) {
			case true:
				switch (action) {
					case Action::Right:
						if (!characterSelector.p1Selected) {
							network.sendPacket << PacketType::OpponentActionPressed << action;
							network.send();
							characterSelector.p1Increment();
						}
						break;
					case Action::Left:
						if (!characterSelector.p1Selected) {
							network.sendPacket << PacketType::OpponentActionPressed << action;
							network.send();
							characterSelector.p1Decrement();
						}
						break;
					case Action::NonA:
						if (!characterSelector.p1Selected) {
							network.sendPacket << PacketType::OpponentActionPressed << action;
							network.send();
							characterSelector.p1Select();
						}
						break;
					case Action::NonB:
						if (characterSelector.p1Selected) {
							network.sendPacket << PacketType::OpponentActionPressed << action;
							network.send();
							characterSelector.p1Deselect();
						}
						break;
				}
				break;
			case false:
				switch (action) {
					case Action::Right:
						if (!characterSelector.p2Selected) {
							network.sendPacket << PacketType::OpponentActionPressed << action;
							network.send();
							characterSelector.p2Increment();
						}
						break;
					case Action::Left:
						if (!characterSelector.p2Selected) {
							network.sendPacket << PacketType::OpponentActionPressed << action;
							network.send();
							characterSelector.p2Decrement();
						}
						break;
					case Action::NonA:
						if (!characterSelector.p2Selected) {
							network.sendPacket << PacketType::OpponentActionPressed << action;
							network.send();
							characterSelector.p2Select();
						}
						break;
					case Action::NonB:
						if (characterSelector.p2Selected) {
							network.sendPacket << PacketType::OpponentActionPressed << action;
							network.send();
							characterSelector.p2Deselect();
						}
						break;
				}
				break;
		}
	}

	if (stageSelector.enabled) {
		if (console.isHosting) {
			switch (action) {
				case Action::Down:
					network.sendPacket << PacketType::OpponentActionPressed << action;
					network.send();
					stageSelector.increment();
					break;
				case Action::Up:
					network.sendPacket << PacketType::OpponentActionPressed << action;
					network.send();
					stageSelector.decrement();
					break;
				case Action::NonA:
					Character& p1 = characterSelector.p1Index;
					Character& p2 = characterSelector.p2Index;
					Stage& stage = stageSelector.index;
					auto timestamp = network.getTimestamp();
					network.sendPacket << PacketType::MatchInit << timestamp << p1 << p2 << stage;
					network.send();
					game.setState(new MatchState(1, timestamp, p1, p2, stage));
					break;
			}
		}
	}
}

void CharacterSelectState::playerActionReleased(Console& console, Network& network, Game& game, Action& action) {}

void CharacterSelectState::opponentActionPressed(Console& console, sf::Packet& packet) {
	Action action;
	packet >> action;

	switch (console.isHosting) {
		case true:
			switch (action) {
				case Action::Right: characterSelector.p2Increment(); break;
				case Action::Left: characterSelector.p2Decrement(); break;
				case Action::NonA: characterSelector.p2Select(); break;
				case Action::NonB: characterSelector.p2Deselect(); break;
			}
			break;
		case false:
			switch (action) {
				case Action::Right: characterSelector.p1Increment(); break;
				case Action::Left: characterSelector.p1Decrement(); break;
				case Action::Down: stageSelector.increment(); break;
				case Action::Up: stageSelector.decrement(); break;
				case Action::NonA: characterSelector.p1Select(); break;
				case Action::NonB: characterSelector.p1Deselect(); break;
			}
			break;
	}
}

void CharacterSelectState::opponentActionReleased(sf::Packet& packet) {}

void CharacterSelectState::update(double& delta) {
	if (characterSelector.enabled && characterSelector.bothSelected()) {
		float time = characterSelector.bothSelectedTimer.getElapsedTime().asSeconds();
		if (time > 3.f) {
			characterSelector.disable();
			characterSelector.hide();
			stageSelector.enable();
			stageSelector.show();
		}
	}
}

void CharacterSelectState::render(sf::RenderWindow& window, Network& network) {
	characterSelector.render(window);
	stageSelector.render(window);
}