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
	void removeEntity(Entity* entityToRemove);
	Entity* addEntity();


private:
	std::vector<std::unique_ptr<Entity>> entities_;
};

