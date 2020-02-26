#pragma once

#include "SDL_Game.h"
#include <vector>
#include <memory>

class Entity;

class EntityManager
{
public:
	EntityManager(SDL_Game* g);
	virtual ~EntityManager();

	void update();
	void draw();
	Entity* addEntity();


private:
	std::vector<std::unique_ptr<Entity>> entities_;
	SDL_Game* game_;

};

