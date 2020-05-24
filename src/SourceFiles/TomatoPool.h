#pragma once

#include "WeaponPool.h"
#include "ObjectPool.h"
#include "Constants.h"


class EntityManager;
class b2World;
class b2Vec2;

class TomatoPool: public WeaponPool {
private:
	ObjectPool<Entity, TOMATO_POOL_SIZE> tomatoPool_;
	int tomatoMaxSpeed_ = 0;
	int tomatoMinSpeed_ = 0;
public:
	TomatoPool();
	~TomatoPool() {};
	virtual void init(EntityManager* eMan, b2World* physicsWorld) override;
	virtual void addWeapon(b2Vec2 pos) override;
	virtual bool isRendering() override { return tomatoPool_.getObj() != nullptr; }
};
