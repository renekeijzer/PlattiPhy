#pragma once
#include "Components.h"
#include <SFML\Graphics.hpp>

struct Behavior : Component<Behavior> {
public:
	virtual void behave() = 0;
	virtual sf::Vector2f getHeading() = 0;
protected:
	sf::Vector2f heading;
};