#include "EntityManager.h"
#include "Entity.h"
#include "Weapon.h"
#include "Component.h"

EntityManager::EntityManager()
{
	for(int i = 0; i<CONST(int,"Z_LAYERS");i++)
	{
		entities_.push_back(std::vector<std::unique_ptr<Entity>>());
	}
}

EntityManager::~EntityManager() {
	entities_.clear();
	externalEntities_.clear();
	weapons_.clear();
}

void EntityManager::update() {
	for (auto& v: entities_)
	{
		for (auto& e : v)
			if (e->isActive()) e->update();
	}
	for (auto& e : externalEntities_)
		if (e->isActive()) e->update();
}

void EntityManager::render() {
	for (auto& v: entities_)
	{
		for (auto& e : v)
			if (e->isActive()) e->render();
	}
	for (auto& e : externalEntities_)
		if (e->isActive()) e->render();
}
void EntityManager::handleInput() {
	for(auto& v: entities_)
		for (auto& e : v)
			if (e->isActive()) e->handleInput();
	for (auto& e : externalEntities_)
		if (e->isActive()) e->handleInput();
}

Entity* EntityManager::addEntity(uint8_t z) {
	Entity* e = new Entity(this);
	//e->setZIndex(z);
	std::unique_ptr<Entity> uPtr(e);
	entities_[z].emplace_back(std::move(uPtr));
	return e;
}

void EntityManager::addExistingEntity(Entity* e) {
	e->setEntityManager(this);
	externalEntities_.push_back(e);
}

std::vector<Weapon*>* EntityManager::getWeaponVector() { return &weapons_; }