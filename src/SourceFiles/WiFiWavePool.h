#pragma once
#include "BulletPool.h"

class WiFiWavePool : public BulletPool
{
private:

public:
	WiFiWavePool() :	BulletPool() {};
	virtual ~WiFiWavePool() {};
	void init(EntityManager* eMan, b2World* physicsWorld, Collider* colRouter);
	void addBullet(b2Vec2 pos, b2Vec2 size, b2Vec2 vel, int texture, int damage, int player) override;
};

