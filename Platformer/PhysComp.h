#include "TheGrid\Component.hpp"
#include "Forces.h"

struct PhysComp : Component<PhysComp>{
private:
	float mass;
	float resitution;
	const float density = 1.2; //density of air 
	Physics::DragCoefficient drag;

};