#pragma once
#include <sfml/Graphics.hpp>
#include "TheGrid\Component.hpp"
#include "Components.h"
/**
* Components checks what direction the player wants to go
*
*/
struct Controlable : public Component<Controlable>
{
public:
	Controlable(){
	}
	direction getNextDirection(){
		for (auto key : keys){
			return key.heading;
		}
		return direction::None;
	}

	struct keyPair{
	public:
		keyPair(sf::Keyboard::Key key, direction inc) : key(key),  heading(inc){}
		sf::Keyboard::Key key;
		direction heading;
	};

private:
	
	direction heading;
	static const keyPair keys[4];
};

enum direction{
	left,
	right,
	up,
	down,
	None
};