#pragma once
#include "ObjectPool.h"
#include "Entity.h"
#include "Constants.h"

class ConfettiPool
{
private:
	ObjectPool<Entity, CONFETTI_POOL_SIZE> confettiPool_;
public:
	ConfettiPool();
	~ConfettiPool() {};
	void init(EntityManager* eMan, b2World* physicsWorld);

	void addConfetti(b2Vec2 pos);
};

