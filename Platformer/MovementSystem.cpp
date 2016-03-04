#include "MovementSystem.h"

void MovementSystem::configure(EventManager & event){
}


void MovementSystem::update(EntityManager & entities, EventManager & events, double dt){




		for (Entity & entity : entities.withComponents<Behavior>()) 
		{
			entity.getComponent<Behavior>()->behave();
			auto & physcicalProperties = entity.getComponent<PhysComp>();

			auto velo = physcicalProperties->calculateSpeed(dt, entity.getComponent<Behavior>()->getHeading());
		}
		resolveCollisions(entities);


	
}


void MovementSystem::resolveCollisions(EntityManager & entities) {
	for (Entity & lhs : entities.withComponents<PhysComp>()) {
		for (Entity & rhs : entities.withComponents<PhysComp>()) {
			if (lhs != rhs) {
				if (PhysComp::AABBCollisionCheck(lhs.getComponent<PhysComp>()->getAABB(), rhs.getComponent<PhysComp>()->getAABB())) {
					PhysComp::resolveCollison(lhs.getComponent<PhysComp>(), rhs.getComponent<PhysComp>());
				}
			}
		}

		auto pComp = lhs.getComponent<PhysComp>();
		auto pos = pComp->getPosition();
		pComp->setPosition(pos + pComp->getVelocity());
	}

}