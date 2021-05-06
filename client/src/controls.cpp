#include <controls.h>

void Controls::start() {
	config.open("src/config.txt");

	setAction(Action::Right);
	setAction(Action::Left);
	setAction(Action::Down);
	setAction(Action::Up);
	setAction(Action::NonA);
	setAction(Action::NonB);
	setAction(Action::SpellA);
	setAction(Action::SpellB);
	setAction(Action::Focus);
	setAction(Action::Bomb);

	config.close();
}

void Controls::setAction(Action action) {
	std::string configKey;
	std::string delimiter = ":";

	std::getline(config, configKey);

	//isolate right side of delimiter
	configKey = configKey.substr(configKey.find(delimiter) + delimiter.length(), configKey.length());

	//remove white space
	configKey.erase(std::remove_if(configKey.begin(), configKey.end(), ::isspace), configKey.end());

	//convert to all lowercase
	std::transform(configKey.begin(), configKey.end(), configKey.begin(), ::tolower);

	//get key mapped to that string
	sf::Keyboard::Key key = keyMap.find(configKey)->second;

	//create key, action pair and insert it
	std::pair<sf::Keyboard::Key, Action> pair(key, action);
	actionMap.insert(pair);
}

Action& Controls::getAction(sf::Keyboard::Key& key) {
	static Action unknown = Action::Unknown;
	auto pair = actionMap.find(key);
	return (pair != actionMap.end()) ? pair->second : unknown;
}
