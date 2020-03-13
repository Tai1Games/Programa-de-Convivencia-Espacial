#include "Entity.h"

Entity::Entity(SDL_Game* game, EntityManager* mngr) :
	entityManager_(mngr),
	game_(game)
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

void Entity::handleInput()
{
	for (auto& c : components_) {
		c->handleInput();
	}
}
