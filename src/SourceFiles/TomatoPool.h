#pragma once
#include "ObjectPool.h"
#include "Entity.h"
#include "Constants.h"

class EntityManager;
class b2World;
class b2Vec2;

class TomatoPool{
private:
	ObjectPool<Entity, TOMATO_POOL_SIZE> tomatoPool_;
public:
	TomatoPool();
	~TomatoPool() {};
	void init(EntityManager* eMan, b2World* physicsWorld);

	void addTomato(b2Vec2 pos);
};