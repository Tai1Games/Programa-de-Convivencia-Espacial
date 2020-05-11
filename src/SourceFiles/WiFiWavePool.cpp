#include "WiFiWavePool.h"

void WiFiWavePool::init(EntityManager* eMan, b2World* physicsWorld, Collider* colRouter)
{
	vector<Entity*> bulletPool = bulletsPool_.getPool();
	for (Entity* e : bulletPool) {
		ObjectFactory::makeWifiWave(e, eMan, physicsWorld, colRouter);
		GETCMP2(e, Bullet)->setActive(false);
	}
}

void WiFiWavePool::addBullet(b2Vec2 pos, b2Vec2 size, b2Vec2 vel, int texture, int damage, int player)
{
	Entity* e = bulletsPool_.getObj();
	if (e != nullptr) {
		GETCMP2(e, Bullet)->setActive(true, pos, size, vel, texture, damage, player);
	}
}