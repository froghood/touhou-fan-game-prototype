#include <network.h>

#include <console.h>
#include <game.h>
#include <state.h>

Network::Network() : offset(0), packetType(0), lastType(0) {}

void Network::start(Console& console, Game& game) {	
	if (console.isHosting) {
		listen(console.port);
		accept(console, game);	
	} else {
		try {connect(console, game);}
		catch (std::string& error) {throw error;}
	}
	socket.setBlocking(false);
	clock.restart();
}

void Network::listen(unsigned short& port) {
	listener.listen(port);
	std::cout << "listening on port " << port << "\n";
}

void Network::accept(Console& console, Game& game) {
	sf::Uint8 status = listener.accept(socket);
	switch (status) {
		case sf::Socket::Done:
			sendPacket << PacketType::Name << console.name;
			send();
			while (!receive(console, game)); //receive name
			std::cout << "player \"" << socketName << "\" connected\n";
			break;
		case sf::Socket::NotReady:
			std::cout << "accept: not ready\n";
			break;
		case sf::Socket::Partial:
			std::cout << "accept: partial\n";
			break;
		case sf::Socket::Disconnected:
			std::cout << "accept: disconnected\n";
			break;
		case sf::Socket::Error:
			std::cout << "accept: error\n";
			break;
	}
}

void Network::connect(Console& console, Game& game) {
	std::cout << "connecting...\n";
	sf::Uint8 status = socket.connect(console.address, console.port, sf::seconds(15));
	
	std::string error;
	switch (status) {
		case sf::Socket::Done:
			sendPacket << PacketType::Name << console.name;
			send();
			while (!receive(console, game)); //receive name
			std::cout << "connected to player \"" << socketName << "\"\n";
			break;
		case sf::Socket::NotReady:
			std::cout << "connect: not ready\n";
			break;
		case sf::Socket::Partial:
			std::cout << "connect: partial\n";
			break;
		case sf::Socket::Disconnected:
			std::cout << "connect: disconnected\n";
			break;
		case sf::Socket::Error:
			//std::cout << "connect: error\n";
			error = "connection timed out";
			break;
	}
	if (!error.empty()) throw error;
}

void Network::send() {
	//std::cout << "sending data...\n";
	sf::Uint8 status = socket.send(sendPacket);
	switch (status) {
		case sf::Socket::Done:
			//std::cout << "send: done\n";
			sendPacket.clear();
			break;
		case sf::Socket::NotReady:
			//std::cout << "send: not ready\n";
			break;
		case sf::Socket::Partial:
			std::cout << "send: partial\n";
			send();
			break;
		case sf::Socket::Disconnected:
			std::cout << "send: disconnected\n";
			break;
		case sf::Socket::Error:
			std::cout << "send: error\n";
			break;

	}
}

bool Network::receive(Console& console, Game& game) {
	sf::Uint8 status = socket.receive(receivePacket);
	std::string error;
	switch (status) {
		case sf::Socket::Done:
			//std::cout << "receive: done\n";
			managePacket(console, game);
			return true;
			break;
		case sf::Socket::NotReady:
			//std::cout << "receive: not ready\n";
			break;
		case sf::Socket::Partial:
			std::cout << "receive: partial\n";
			break;
		case sf::Socket::Disconnected:
			error = "opponent disconnected";	
			break;
		case sf::Socket::Error:
			std::cout << "receive: error\n";
			break;
	}
	if (!error.empty()) throw error;
	return false;
}

void Network::managePacket(Console& console, Game& game) {
	PacketType packetType;
	receivePacket >> packetType;
	switch (packetType) {
		case PacketType::Name:
			//std::cout << "received name (" << packetType << ")\n";
			std::cout << "packet: name\n";
			name();
			break;
		case PacketType::SyncStart:
			std::cout << "packet: syncStart\n";
			syncStart();
			break;
		case PacketType::Sync:
			//std::cout << "packet: sync\n";
			sync();
			break;
		case PacketType::OpponentActionPressed:
			std::cout << "packet: opponentActionPressed\n";
			game.state->opponentActionPressed(console, receivePacket);
			break;
		case PacketType::OpponentActionReleased:
			game.state->opponentActionReleased(receivePacket);
			break;
		case PacketType::MatchInit:
			matchInit(game);
			break;
		case PacketType::OpponentVelocityChange:
			game.state->opponentVelocityChange(*this, receivePacket);
			break;
		case PacketType::OpponentGraze:
			game.state->opponentGraze(receivePacket);
			break;
		case PacketType::OpponentHit:
			game.state->opponentHit(receivePacket);
			break;
		default:
			std::cout << "no data matches\n";
			break;
	}
}


//packet methods
void Network::name() {
	receivePacket >> socketName;
	//std::cout << receivePacket << "\n";
	//std::cout << "received " << lastType << ", " << socketName << "\n";
}

void Network::syncStart() {
	sf::Int64 receivedTimestamp;
	receivePacket >> receivedTimestamp;

	sf::Int64 timestamp = getTimestamp();
	sf::Int64 latency = timestamp - receivedTimestamp;
	sendPacket << PacketType::Sync << timestamp << latency;
	send();
}

void Network::sync() {
	sf::Int64 receivedTimestamp;
	sf::Int64 receivedLatency;
	receivePacket >> receivedTimestamp >> receivedLatency;

	sf::Int64 timestamp = getTimestamp();
	sf::Int64 latency = timestamp - receivedTimestamp;
	sf::Int64 latencyDifference = latency - receivedLatency;

	sf::Int64 latencyFix = sf::Int64(latencyDifference * 0.2 + 0.5);
	offset -= latencyFix;
	latency += latencyFix;

	timestamp = getTimestamp();
	sendPacket << PacketType::Sync << timestamp << latency;
	send();
}

void Network::matchInit(Game& game) {
	Character p1, p2;
	Stage stage;
	sf::Uint64 timestamp;
	receivePacket >> timestamp >> p1 >> p2 >> stage;
	game.setState(new MatchState(2, timestamp, p1, p2, stage));
}

sf::Uint64 Network::getTimestamp() {
	return clock.getElapsedTime().asMicroseconds() + offset;
}

//returns the difference in timestamps as a decimal
double Network::getLatency(sf::Uint64& t) {
	auto ct = getTimestamp();
	return (t > ct) ? 0.0 : (ct - t) / 1000000.0;
}
