#pragma once
#include "TheGrid\EntityManager.hpp"

#include <SFML\Graphics.hpp>

#include "Components.h"

class EntityFactory
{
public:
	Entity createHumanoid(sf::Vector2f pos);
	static EntityFactory* get(EntityManager & manager);
private:
	static EntityFactory * Instance;
	EntityManager & manager;
	EntityFactory(EntityManager & man) : manager(man){}
};

