#pragma once
#include "TheGrid\Component.hpp"
#include "Behavior.h"

struct BlockBehavior : Behavior {
public:

	//ain't gonna do shit
	//I'm a motherfucking block
	void behave() {}
	sf::Vector2f getHeading() {
		return heading;
	}
};