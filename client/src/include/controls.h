#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>

#include <action.h>

struct Controls {
	std::ifstream config;

	void start();
	void setAction(Action action);
	Action& getAction(sf::Keyboard::Key& key);

	std::unordered_map<sf::Keyboard::Key, Action> actionMap;

	std::unordered_map<std::string, sf::Keyboard::Key> keyMap{
		{"a", sf::Keyboard::Key::A},
		{"b", sf::Keyboard::Key::B},
		{"c", sf::Keyboard::Key::C},
		{"d", sf::Keyboard::Key::D},
		{"e", sf::Keyboard::Key::E},
		{"f", sf::Keyboard::Key::F},
		{"g", sf::Keyboard::Key::G},
		{"h", sf::Keyboard::Key::H},
		{"i", sf::Keyboard::Key::I},
		{"j", sf::Keyboard::Key::J},
		{"k", sf::Keyboard::Key::K},
		{"l", sf::Keyboard::Key::L},
		{"m", sf::Keyboard::Key::M},
		{"n", sf::Keyboard::Key::N},
		{"o", sf::Keyboard::Key::O},
		{"p", sf::Keyboard::Key::P},
		{"q", sf::Keyboard::Key::Q},
		{"r", sf::Keyboard::Key::R},
		{"s", sf::Keyboard::Key::S},
		{"t", sf::Keyboard::Key::T},
		{"u", sf::Keyboard::Key::U},
		{"v", sf::Keyboard::Key::V},
		{"w", sf::Keyboard::Key::W},
		{"x", sf::Keyboard::Key::X},
		{"y", sf::Keyboard::Key::Y},
		{"z", sf::Keyboard::Key::Z},
		{"space", sf::Keyboard::Key::Space},
		{"shift", sf::Keyboard::Key::LShift},
		{"ctrl", sf::Keyboard::Key::LControl},
		{"alt", sf::Keyboard::Key::LAlt},
		{"tab", sf::Keyboard::Key::Tab},
		{"right", sf::Keyboard::Key::Right},
		{"left", sf::Keyboard::Key::Left},
		{"down", sf::Keyboard::Key::Down},
		{"up", sf::Keyboard::Key::Up},
	};
};