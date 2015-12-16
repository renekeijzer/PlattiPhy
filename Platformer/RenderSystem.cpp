#include "RenderSystem.h"

void RenderSystem::configure(EventManager & event){
}


void RenderSystem::update(EntityManager & entities, EventManager & events, double dt){

	for (Entity & ent : entities.withComponents<Renderable>()){
		Renderable::Handle & render = ent.getComponent<Renderable>();
		if (ent.hasComponent<Moveable>()){
			render->setPosition(ent.getComponent<Moveable>()->getPosition());
		}
		target.draw(*render->shape.get());	
	}
}