#include "EntityFactory.hpp"

EntityFactory * EntityFactory::Instance = nullptr;


EntityFactory* EntityFactory::get(EntityManager& manager){
	if (!Instance){
		Instance = new EntityFactory(manager);
	}
	return Instance;
}

Entity EntityFactory::createHumanoid(sf::Vector2f pos){
	Entity ent = manager.createEntity();
	std::unique_ptr<sf::Shape> shape(new sf::RectangleShape(sf::Vector2f(32, 32)));
	shape->setFillColor(sf::Color::White);
	shape->setPosition(pos);

	ent.addComponent<Moveable>();
	ent.getComponent<Moveable>()->setPosition(pos);
	ent.addComponent<Controlable>();
	ent.addComponent<Renderable>(std::move(shape));


	return ent;
}

