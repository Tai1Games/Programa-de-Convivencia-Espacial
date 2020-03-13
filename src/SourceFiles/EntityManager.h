#pragma once

#include <vector>
#include <memory>
#include "checkML.h"


class Entity;
class SDL_Game;

class EntityManager
{
public:
	EntityManager(SDL_Game* game);
	virtual ~EntityManager();

	void update();
	void render();
	void handleInput();
	Entity* addEntity();


private:
	SDL_Game* game_;
	std::vector<std::unique_ptr<Entity>> entities_;
};

