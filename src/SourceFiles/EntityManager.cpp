#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager(SDL_Game* game): game_(game){}

EntityManager::~EntityManager() {
	entities_.clear();
}

void EntityManager::update() {
	for (auto& e : entities_) {
		e->update();
	}
}

void EntityManager::render() {
	for (auto& e : entities_) {
		e->render();
	}
}
void EntityManager::handleInput() {
	for (auto& e : entities_) {
		e->handleInput();
	}
}


Entity* EntityManager::addEntity() {
	Entity* e = new Entity(game_, this);
	std::unique_ptr<Entity> uPtr(e);
	entities_.emplace_back(std::move(uPtr));
	return e;
}
