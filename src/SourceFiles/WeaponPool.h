#pragma once

#include "b2_math.h"
#include "Entity.h"

class WeaponPool {
public:
	WeaponPool(){}
	~WeaponPool(){}
	virtual void init(EntityManager* eMan, b2World* physicsWorld) = 0;
	virtual void addWeapon(b2Vec2 pos) = 0;
	virtual bool isRendering() = 0;
};
