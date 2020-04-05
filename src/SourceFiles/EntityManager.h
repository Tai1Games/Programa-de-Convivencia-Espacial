#pragma once

#include <vector>
#include <memory>
#include "checkML.h"

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


private:
	std::vector<std::unique_ptr<Entity>> entities_;
};

