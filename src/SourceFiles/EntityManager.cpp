#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager() {}

EntityManager::~EntityManager() {
	entities_.clear();
	externalEntities_.clear();
}

void EntityManager::update() {
	for (auto& e : entities_) {
		if(e->isActive())
			e->update();
	}
	for (auto e : externalEntities_)
		if (e->isActive())
			e->update();
}

void EntityManager::render() {
	for (auto& e : entities_) {
		e->render();
	}
	for (auto e : externalEntities_) e->render();
}
void EntityManager::handleInput() {
	for (auto& e : entities_) {
		e->handleInput();
	}
	for (auto e : externalEntities_) e->handleInput();
}

Entity* EntityManager::addEntity() {
	Entity* e = new Entity(this);
	std::unique_ptr<Entity> uPtr(e);
	entities_.emplace_back(std::move(uPtr));
	return e;
}

void EntityManager::addExistingEntity(Entity* e) {
	e->setEntityManager(this);
	externalEntities_.push_back(e);
}
