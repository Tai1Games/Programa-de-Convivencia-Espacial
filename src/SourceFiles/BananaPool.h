#pragma once
#include "ObjectPool.h"
#include "Entity.h"
#include "BananaWeapon.h"
#include "ObjectFactory.h"

class BananaPool
{
private :
	ObjectPool<Entity, 10> bananaPool_; //de 10 bananas de momento

public:
	BananaPool();
	~BananaPool(){}
	void init(EntityManager* eMan, b2World* physicsWorld);
	void addBanana(b2Vec2 pos);
};