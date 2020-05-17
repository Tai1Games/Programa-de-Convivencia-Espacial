#include "StaplerPool.h"
#include "StaplerWeapon.h"
#include "WeaponFactory.h"

StaplerPool::StaplerPool() : staplerPool_([](Entity* e) {return e->isActive(); }) {};

void StaplerPool::init(EntityManager* eMan, b2World* physicsWorld, BulletPool* bP)
{
	b2Vec2 staplerSize = b2Vec2(CONST(float, "STAPLER_X"), CONST(float, "STAPLER_Y"));
	vector<Entity*> staplerPoolVec = staplerPool_.getPool();
	for (Entity* e : staplerPoolVec) {
		e = WeaponFactory::makeStapler(e, eMan, physicsWorld, b2Vec2(0, 0), staplerSize, bP);
		e->getComponent<StaplerWeapon>(ComponentType::StaplerWeapon)->setActive(false);
	}
}

Entity* StaplerPool::addStapler(b2Vec2 pos)
{
	Entity* e = staplerPool_.getObj();
	if (e != nullptr) {
		StaplerWeapon* stapler = e->getComponent<StaplerWeapon>(ComponentType::StaplerWeapon);
		stapler->setActive(true, pos);
	}

	return e;
}
