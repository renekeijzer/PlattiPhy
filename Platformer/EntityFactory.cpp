#include "EntityFactory.hpp"

EntityFactory * EntityFactory::Instance = nullptr;


EntityFactory* EntityFactory::get(EntityManager& manager){
	if (!Instance){
		Instance = new EntityFactory(manager);
	}
	return Instance;
}

Entity EntityFactory::createHumanoid(sf::Vector2f pos, sf::Vector2f size){
	Entity ent = manager.createEntity();
	
	std::unique_ptr<sf::Shape> shape(new sf::RectangleShape(size));
	shape->setFillColor(sf::Color::White);
	shape->setPosition(pos);
	
	ent.addComponent<PhysComp>(
		sf::Vector2f(1, 1),
		0.3,
		size,
		pos, 
		80
	);
	ent.addComponent<Moveable>();
	
	
	ent.addComponent<PlayerBehavior>();
	ent.addComponent<Renderable>(std::move(shape));


	return ent;
}




Entity EntityFactory::createParticle(sf::Vector2f pos)
{
	Entity ent = manager.createEntity();

	std::unique_ptr<sf::Shape> shape(new sf::RectangleShape(sf::Vector2f(2, 2)));
	shape->setFillColor(sf::Color::Yellow);
	shape->setPosition(pos);

	ent.addComponent<PhysComp>(
		sf::Vector2f(10, 10),
		0.1,
		sf::Vector2f(2,2),
		pos,
		0.5
	);

	ent.addComponent<Renderable>(std::move(shape));
	ent.addComponent<ParticleBehavior>();
	return ent;
}

Entity EntityFactory::createBlock(sf::Vector2f pos, sf::Vector2f size, float mass)
{
	Entity ent = manager.createEntity();

	std::unique_ptr<sf::Shape> shape(new sf::RectangleShape(size));
	shape->setFillColor(sf::Color::Blue);
	shape->setPosition(pos);

	ent.addComponent<PhysComp>(
		sf::Vector2f(10,10),
		0.7,
		size,
		pos,
		mass
		);

	ent.addComponent<BlockBehavior>();
	ent.addComponent<Renderable>(std::move(shape));
	return ent;
}

