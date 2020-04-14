#pragma once
#include "box2d.h"
class Entity;
struct Collision
{
public:
	Collision(const  b2Fixture* other, const b2Contact* contactInfo,const Entity* e) :
		entity(e),
		contact(contactInfo),
		fixture(other) {}
	
	const Entity* entity = nullptr;
	const b2Contact* contact = nullptr;
	const b2Fixture* fixture = nullptr;
};

