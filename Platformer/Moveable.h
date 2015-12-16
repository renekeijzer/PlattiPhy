#pragma once
#include <sfml/Graphics.hpp>
#include "TheGrid\Component.hpp"

struct Moveable : public Component<Moveable>
{
public:
	void setPosition(sf::Vector2f pos){ compPosition = pos; }
	sf::Vector2f getPosition(){ return compPosition; }

	void setVelocity(sf::Vector2f velo){ compVelocity = velo; }
	sf::Vector2f getVelocity(){ return compVelocity; }

	void setHeading(sf::Vector2f head){ compHeading = head;}
	sf::Vector2f getHeading(){ return compHeading; }

	void move(){
		compPosition += compVelocity;
	}


private:
	sf::Vector2f compVelocity;
	sf::Vector2f compPosition;


	sf::Vector2f compHeading;
};