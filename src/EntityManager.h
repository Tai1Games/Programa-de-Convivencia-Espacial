#pragma once

#include <vector>
#include <memory>

class Entity;
class SDL_Game;

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

