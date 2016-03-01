#include "TheGrid\Component.hpp"
#include "Behavior.h"
#include <SFML\Graphics.hpp>
struct PlayerBehavior : Behavior{
public:
	void behave() {
		heading.x = 0, heading.y = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			heading.x = -1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			heading.x = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			heading.y = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			heading.y = -1;

	}

	sf::Vector2f getHeading() {
		return heading;
	}
	
};