#pragma once
#include "Behavior.h"
#include <cstdlib>

struct ParticleBehavior : Behavior
{
public:
	void behave() {
		heading.x = (rand() % 3) - 1;
		heading.y = (rand() % 3) - 1;
	}

	sf::Vector2f getHeading() {
		return heading;
	}

};