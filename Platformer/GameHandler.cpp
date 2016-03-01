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
	factory->createHumanoid(pos, sf::Vector2f(32,32));

	auto view = target.getViewport(target.getDefaultView());
	for (int i = 0; i < 10; i++) {
		factory->createParticle(sf::Vector2f(rand() %  view.width, rand() % view.height));
	}

	factory->createBlock(sf::Vector2f(100, 100), sf::Vector2f(32, 32), 80);
	factory->createBlock(sf::Vector2f(200, 200), sf::Vector2f(16, 16), 40);
	factory->createBlock(sf::Vector2f(400, 400), sf::Vector2f(64, 64), 160);
	factory->createBlock(sf::Vector2f(1000, 500), sf::Vector2f(128, 128), 320);


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