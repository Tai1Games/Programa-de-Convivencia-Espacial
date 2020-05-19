#pragma once
#include "ObjectPool.h"
#include "Entity.h"
#include "Constants.h"

class GameMode;

class ConfettiPool
{
private:
	ObjectPool<Entity, CONFETTI_POOL_SIZE> confettiPool_;
public:
	ConfettiPool();
	virtual ~ConfettiPool() {};
	void init(EntityManager* eMan, b2World* physicsWorld);

	Entity* addConfetti(b2Vec2 pos);
};
