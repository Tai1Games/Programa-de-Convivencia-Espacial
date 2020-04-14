#pragma once
#include "box2d.h"
class Entity;
class CollisionHandler;
struct Collision
{
public:
	Collision(b2Fixture* other,b2Contact* contactInfo,Entity* e,CollisionHandler* hndler) :
		entity(e),
		contact(contactInfo),
		fixture(other),
		collisionHandler(hndler){}
	
	CollisionHandler* collisionHandler = nullptr;
	Entity* entity = nullptr;
	b2Contact* contact = nullptr;
	b2Fixture* fixture = nullptr;
};

