#include "Controlable.h"

const Controlable::keyPair Controlable::keys[4] = {
	{ sf::Keyboard::Key::A, direction::left,
	{ sf::Keyboard::Key::D, direction::right },
	{ sf::Keyboard::Key::W, direction::up },
	{ sf::Keyboard::Key::S, direction::down }
};