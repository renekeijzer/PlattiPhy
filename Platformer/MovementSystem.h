#pragma once

#include "TheGrid\SystemManager.hpp"
#include "TheGrid\EntityManager.hpp"
#include "TheGrid\EventManager.hpp"

#include "Components.h"

class MovementSystem : public System<MovementSystem>
{
public:
	MovementSystem(sf::RenderWindow & tar) : target(tar){}
	void configure(EventManager & events) override;
	void update(EntityManager & entities, EventManager & events, double dt);
private:
	sf::RenderWindow & target;
};

