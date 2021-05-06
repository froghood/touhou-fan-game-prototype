#pragma once

#pragma warning(push, 0)
#include <SFML/Network/IpAddress.hpp>
#pragma warning(pop)

#include <iostream>
#include <string>

struct Console {
	std::string name;
	bool isHosting;
	sf::IpAddress address;
	unsigned short port;

	Console();
	void start(bool useDefault);
	void askName();
	void askIsHosting();
	void askAddress();
	void askPort();
};