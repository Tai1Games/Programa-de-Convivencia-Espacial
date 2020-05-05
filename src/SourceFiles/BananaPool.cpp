#include "BananaPool.h"

BananaPool::BananaPool():bananaPool_([](Entity* e) {return e->isActive(); })
{
}

void BananaPool::init(EntityManager* eMan, b2World* physicsWorld, BulletPool* bp)
{
	vector<Entity*> bananaPool = bananaPool_.getPool();
	for (Entity* e : bananaPool) {
		ObjectFactory::makeBanana(e, eMan, physicsWorld, b2Vec2(0, 0), bp);
		e->getComponent<BananaWeapon>(ComponentType::Banana)->setActive(false);
	}
}

void BananaPool::addBanana(b2Vec2 pos)
{
	Entity* e = bananaPool_.getObj();
	if (e != nullptr) {
		e->getComponent<BananaWeapon>(ComponentType::Banana)->setActive(true, pos);
	}
}
