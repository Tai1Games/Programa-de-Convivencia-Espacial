#pragma once
#include "ObjectPool.h"
#include "Entity.h"
#include "ObjectFactory.h"
#include "Bullet.h"

class BulletPool
{
protected:
	ObjectPool<Entity, 10> bulletsPool_; //PROVISIONAL
public:
	BulletPool();
	~BulletPool() {}
	
	virtual void init(EntityManager* eMan, b2World* physicsWorld);
	virtual void addBullet(b2Vec2 pos, b2Vec2 size, b2Vec2 vel, int texture, int damage, int player);

	void addThrownByPlayer(GameMode* gm);
};

