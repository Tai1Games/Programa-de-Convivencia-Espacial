#pragma once

#include "ObjectPool.h"
#include "Constants.h"
#include "Entity.h"
#include "Collider.h"

class BodyPool {
public:
	BodyPool() : bodyPool_([](Entity* e) { return e->isActive(); }) {};
	~BodyPool() {};
	void init(EntityManager* eMan, b2World* physicsWorld, vector<Collider*>& collDeadBodies, vector<Entity*>& deadBodies);
	void addBody(b2Vec2 pos, float angle, b2Vec2 linearVelocity, float angularVelocity);
private:
	ObjectPool<Entity, BODY_POOL_SIZE> bodyPool_;
	int oldestBody_ = 0;
	bool isFull = false;
};
