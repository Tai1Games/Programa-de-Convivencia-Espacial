#pragma once
#include "box2d.h"
class Entity;
class CollisionHandler;
struct Collision
{
public:
	Collision(b2Fixture* other,b2Contact* contactInfo,Entity* e,CollisionHandler* hndler, b2Fixture* mFix) :
		entity(e),
		contact(contactInfo),
		hitFixture(other),
		collisionHandler(hndler),
		myFixture(mFix){}
	
	CollisionHandler* collisionHandler = nullptr;  
	Entity* entity = nullptr;
	b2Contact* contact = nullptr;
	b2Fixture* hitFixture = nullptr;
	b2Fixture* myFixture = nullptr;
};

