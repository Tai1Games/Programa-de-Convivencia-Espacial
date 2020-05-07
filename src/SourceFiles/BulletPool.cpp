#include "BulletPool.h"
#include "ThrownByPlayer.h"

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

void BulletPool::addBullet(b2Vec2 pos, b2Vec2 size, b2Vec2 vel,int texture, int damage, int player)
{
	Entity* e = bulletsPool_.getObj();
	if (e != nullptr) {
		e->getComponent<ThrownByPlayer>(ComponentType::ThrownByPlayer)->SetOwner(player);
		e->getComponent<Bullet>(ComponentType::Bullet)->setActive(true, pos, size, vel,texture, damage, player);
	}
}

void BulletPool::addThrownByPlayer(GameMode* gm)
{
	vector<Entity*> bulletPool = bulletsPool_.getPool();
	for (Entity* e : bulletPool) {
		e->addComponent<ThrownByPlayer>(gm);
	}
}
