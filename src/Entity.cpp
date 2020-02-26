#include "Entity.h"

Entity::Entity(SDL_Game* game, EntityManager* mngr) :
	game_(game), //
	mngr_(mngr) //
{
}

Entity::~Entity() {
}