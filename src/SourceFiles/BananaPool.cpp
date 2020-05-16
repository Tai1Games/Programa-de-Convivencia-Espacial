#include "BananaPool.h"
#include "BananaWeapon.h"
#include "Entity.h"
#include "ObjectFactory.h"

BananaPool::BananaPool(BulletPool* bp) : bananaPool_([](Entity* e) { return e->isActive(); }), bulletPool_(bp) {};

void BananaPool::init(EntityManager* eMan, b2World* physicsWorld) {
	vector<Entity*> bananaPool = bananaPool_.getPool();
	bananaMaxSpeed_ = CONST(int, "BANANA_MAX_SPEED");
	bananaMinSpeed_ = CONST(int, "BANANA_MIN_SPEED");
	for (Entity* e : bananaPool) {
		ObjectFactory::makeBanana(e, eMan, physicsWorld, b2Vec2(0, 0), bulletPool_);
		e->getComponent<BananaWeapon>(ComponentType::Weapon)->setActive(false);
	}
}

void BananaPool::addWeapon(b2Vec2 pos) {
	Entity* e = bananaPool_.getObj();
	if (e != nullptr) {
		BananaWeapon* banana = e->getComponent<BananaWeapon>(ComponentType::Weapon);
		banana->setActive(true, pos);
		int randDirX = -1;
		int randDirY = -1;
		if (rand() % 2 == 1) randDirX = 1;
		if (rand() % 2 == 1) randDirY = 1;
		e->getComponent<Collider>(ComponentType::Collider)->applyForce(b2Vec2((rand() % bananaMaxSpeed_ * randDirX) + bananaMinSpeed_, 
			(rand() % bananaMaxSpeed_ * randDirY) + bananaMinSpeed_), b2Vec2(0, 0));
	}
}
