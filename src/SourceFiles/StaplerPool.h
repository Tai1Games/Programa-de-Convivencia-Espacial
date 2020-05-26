#pragma once
#include "ObjectPool.h"
#include "Entity.h"
#include "Constants.h"

class BulletPool;

class StaplerPool
{
private:
	ObjectPool<Entity, STAPLER_POOL_SIZE> staplerPool_;
public:
	StaplerPool();
	virtual ~StaplerPool() {};
	void init(EntityManager* eMan, b2World* physicsWorld, BulletPool* bP);

	Entity* addStapler(b2Vec2 pos);
};
