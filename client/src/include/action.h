#pragma once

#include <SFML/Config.hpp>

const enum class Action : sf::Uint8 {
	Right,
	Left,
	Down,
	Up,
	NonA,
	NonB,
	SpellA,
	SpellB,
	Focus,
	Bomb,
	Unknown
};