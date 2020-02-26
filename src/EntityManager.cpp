#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager(SDL_Game* game) :
	game_(game) {
}

EntityManager::~EntityManager() {
}

void EntityManager::update() {
	for (auto& e : entities_) {
		e->update();
	}
}

void EntityManager::draw() {
	for (auto& e : entities_) {
		e->draw();
	}
}

Entity* EntityManager::addEntity() {
	Entity* e = new Entity(game_, this);
	std::unique_ptr<Entity> uPtr(e);
	entities_.emplace_back(std::move(uPtr));
	return e;
}
