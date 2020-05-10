#pragma once

#include "WeaponPool.h"
#include "ObjectPool.h"
#include "Constants.h"
#include "BulletPool.h"


class EntityManager;
class b2World;
class b2Vec2;

class BananaPool : public WeaponPool {
private:
	ObjectPool<Entity, BANANA_POOL_SIZE> bananaPool_;
	int bananaMaxSpeed_ = 0;
	int bananaMinSpeed_ = 0;
	BulletPool* bulletPool_ = nullptr;
public:
	BananaPool(BulletPool* bp);
	~BananaPool() {};
	virtual void init(EntityManager* eMan, b2World* physicsWorld) override;
	virtual void addWeapon(b2Vec2 pos) override;
};