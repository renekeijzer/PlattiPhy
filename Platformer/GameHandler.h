
#pragma once
#include <SFML\Graphics.hpp>

#include "TheGrid\EntityManager.hpp"


#include "Systems.h"
#include "EntityFactory.hpp"

class GameHandler
{
public:
	GameHandler();
	~GameHandler();
	void run();
private:
	void init(sf::RenderWindow & target);
	void loadContent();

	void update(double deltaTime);


	sf::Font font;
	
	EntityManager entityManager;
	EventManager eventManager;
	SystemManager systemManager;
	Analytics * an = nullptr;
	EntityFactory * factory = nullptr;
};

