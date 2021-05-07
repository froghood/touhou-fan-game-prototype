#pragma once

#include <iostream>
#include <thread>

#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/SocketSelector.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>

struct Console;
struct Game;
struct State;

struct Network {

	sf::Clock clock;
	sf::Int64 offset;

	sf::TcpListener listener;
	sf::TcpSocket socket;
	std::string socketName;	
	sf::SocketSelector selector;

	sf::Packet sendPacket;
	sf::Packet receivePacket;
	sf::Uint8 packetType;
	sf::Uint8 lastType;

	Network();
	void start(Console& console, Game& game);

	void listen(unsigned short& port);
	void accept(Console& console, Game& game);
	void connect(Console& console, Game& game);

	void send();
	bool receive(Console& console, Game& game);
	void managePacket(Console& console, Game& game);

	sf::Uint64 getTimestamp();
	double getLatency(sf::Uint64& t);

	void name();
	void syncStart();
	void sync();
	void matchInit(Game& game);
};

const enum class PacketType : sf::Uint8 {
	Name,
	SyncStart,
	Sync,
	OpponentActionPressed,
	OpponentActionReleased,
	MatchInit,
	OpponentVelocityChange,
	OpponentGraze,
	OpponentHit,
};

inline sf::Packet& operator << (sf::Packet& packet, sf::Vector2<double>& v) {
	return packet << v.x << v.y;
}

inline sf::Packet& operator >> (sf::Packet& packet, sf::Vector2<double>& v) {
	return packet >> v.x >> v.y;
}

template<typename T>
sf::Packet& operator << (sf::Packet& packet, const T& e) {
	return packet << static_cast<sf::Uint8>(e);
}

template<typename T>
sf::Packet& operator >> (sf::Packet& packet, T& e) {
	sf::Uint8 n;
	packet >> n;
	e = static_cast<T>(n);
	return packet;
}
