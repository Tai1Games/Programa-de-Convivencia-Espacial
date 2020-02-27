#pragma once

#include <vector>
#include <memory>

class Entity;
class SDL_Game;

class EntityManager
{
public:
	EntityManager();
	virtual ~EntityManager();

	void update();
	void render();
	Entity* addEntity();


private:
	std::vector<std::unique_ptr<Entity>> entities_;
};

