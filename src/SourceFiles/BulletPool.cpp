#include "BulletPool.h"

BulletPool::BulletPool() :bulletsPool_([](Entity* e) {return e->isActive(); })
{

}

void BulletPool::init(EntityManager* eMan, b2World* physicsWorld)
{
	vector<Entity*> bulletPool = bulletsPool_.getPool();
	for (Entity* e : bulletPool) {
		ObjectFactory::makeBullet(e, eMan, physicsWorld);
		e->getComponent<Bullet>(ComponentType::Bullet)->setActive(false);
	}
}

void BulletPool::addBullet(b2Vec2 pos, b2Vec2 size, b2Vec2 vel,int texture, int damage)
{
	Entity* e = bulletsPool_.getObj();
	if (e != nullptr) {
		e->getComponent<Bullet>(ComponentType::Bullet)->setActive(true, pos, size, vel,texture, damage);
	}
}
