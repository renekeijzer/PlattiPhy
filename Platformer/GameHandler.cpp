#include "GameHandler.h"


GameHandler::GameHandler() : systemManager(entityManager, eventManager)
{	

	loadContent();

	an = Analytics::get(entityManager, systemManager, eventManager);
	factory = EntityFactory::get(entityManager);
}


void GameHandler::init(sf::RenderWindow & target){
	systemManager.addSystem<MovementSystem>(target);
	systemManager.addSystem<RenderSystem>(target);
	systemManager.configure();
}

void GameHandler::loadContent(){

}


void GameHandler::run(){

	sf::RenderWindow target(sf::VideoMode::getDesktopMode(), "Platformer", sf::Style::Default);
	init(target);
	sf::Clock clock;
	sf::Vector2f pos(32, 32);
	factory->createHumanoid(pos);

	while (target.isOpen()) {
		sf::Event event;
		while (target.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				target.close();
				break;
			default:
				break;
			}
		}

		target.clear();
		sf::Time elapsed = clock.getElapsedTime();
		clock.restart();
		update(static_cast<double>(elapsed.asSeconds()));

		target.display();
		

	}
}

void GameHandler::update(double deltaTime){
	systemManager.update<MovementSystem>(deltaTime);
	systemManager.update<RenderSystem>(deltaTime);
	an->log();
}


GameHandler::~GameHandler(){
	delete an;
}