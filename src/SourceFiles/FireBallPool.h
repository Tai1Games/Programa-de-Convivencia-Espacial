#pragma once
#include "ObjectPool.h"
#include "Entity.h"
#include "Constants.h"

class EntityManager;
class b2World;
class b2Vec2;

class FireBallPool
{
private:
	ObjectPool<Entity, FIREBALL_POOL_SIZE> fireballPool_;
public:
	FireBallPool();
	~FireBallPool() {}
	void init(EntityManager* eMan, b2World* physicsWorld);

	void addFireBall(b2Vec2 pos, b2Vec2 impulse);
};

