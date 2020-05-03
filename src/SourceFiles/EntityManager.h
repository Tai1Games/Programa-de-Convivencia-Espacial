#pragma once

#include <vector>
#include <memory>
#include "checkML.h"

class Weapon;
class Entity;
class SDL_Game;

class EntityManager
{
public:
	EntityManager();
	virtual ~EntityManager();

	void update();
	void render();
	void handleInput();
	Entity* addEntity();
	void addExistingEntity(Entity* e);

	std::vector<Weapon*>* getWeaponVector();

private:
	std::vector<std::unique_ptr<Entity>> entities_;
	std::vector<Entity*> externalEntities_;
	std::vector<Weapon*> weapons_;
};

