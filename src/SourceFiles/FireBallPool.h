#pragma once
#include "ObjectPool.h"
#include "Entity.h"

class EntityManager;
class b2World;
class b2Vec2;

class FireBallPool
{
private:
	ObjectPool<Entity, 20> fireballPool_;
	int fireballW_, fireballH_, fireballSpeed_;
public:
	FireBallPool();
	~FireBallPool() {}
	void init(EntityManager* eMan, b2World* physicsWorld);

	void addFireBall(b2Vec2 pos, b2Vec2 impulse);
};

