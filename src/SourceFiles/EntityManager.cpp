#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager() {}

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

void EntityManager::removeEntity(Entity* entityToRemove)
{
	vector<std::unique_ptr<Entity>>::iterator it = entities_.begin();

	while (it->get() != entityToRemove && it != entities_.end()) {
		++it;
	}
	if (it != entities_.end()) {
		entities_.erase(it);
	}
}


Entity* EntityManager::addEntity() {
	Entity* e = new Entity(this);
	std::unique_ptr<Entity> uPtr(e);
	entities_.emplace_back(std::move(uPtr));
	return e;
}
