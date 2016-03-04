#include "Components.h"
#ifndef __MANIFOLD__
#define __MANIFOLD__
struct PhysComp;
struct Manifold {
public:
	Manifold(ComponentHandle<PhysComp> & lhs, ComponentHandle<PhysComp> & rhs) : lhs(lhs), rhs(rhs) {}
	ComponentHandle<PhysComp> & rhs;
	ComponentHandle<PhysComp> & lhs;
	float penetration;
	sf::Vector2f normal;
}; 
#endif