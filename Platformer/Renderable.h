#pragma once
#include <SFML\Graphics.hpp>
#include "TheGrid\Component.hpp"

struct Renderable : public Component<Renderable>{
public:
	explicit Renderable(std::unique_ptr<sf::Shape> &shape) : shape(std::move(shape)) {}

	void setColor(sf::Color col){
		shape->setFillColor(col);
	}

	void setPosition(sf::Vector2f position){
		shape->setPosition(position); 
	}
	std::unique_ptr<sf::Shape> shape;
private:
	

	
};