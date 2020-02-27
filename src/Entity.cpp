#include "Entity.h"

Entity::Entity( EntityManager* mngr) :
	entityManager_(mngr) //
{
}

Entity::~Entity() {
}

void Entity::update()
{
	for (auto& c : components_) {
		c->update();
	}
}

void Entity::render()
{
	for (auto& c : components_) {
		c->draw();
	}
}
