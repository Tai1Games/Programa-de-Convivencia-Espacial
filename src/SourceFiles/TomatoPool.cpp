#include "TomatoPool.h"
#include "TomatoWeapon.h"
#include "Entity.h"
#include "ObjectFactory.h"

TomatoPool::TomatoPool() : tomatoPool_([](Entity* e) { return e->isActive(); }) {};

void TomatoPool::init(EntityManager* eMan, b2World* physicsWorld) {
	vector<Entity*> tomatoPool = tomatoPool_.getPool();
	tomatoMaxSpeed_ = CONST(int, "TOMATO_MAX_SPEED");
	tomatoMinSpeed_ = CONST(int, "TOMATO_MIN_SPEED");
	for (Entity* e : tomatoPool) {
		ObjectFactory::makeTomato(e, eMan, physicsWorld, b2Vec2(0, 0));
		e->getComponent<TomatoWeapon>(ComponentType::Weapon)->setActive(false);
	}
}

void TomatoPool::addWeapon(b2Vec2 pos) {
	Entity* e = tomatoPool_.getObj();
	if (e != nullptr) {
		TomatoWeapon* tomato = e->getComponent<TomatoWeapon>(ComponentType::Weapon);
		tomato->setActive(true, pos);
		int randDirX = -1;
		int randDirY = -1;
		if (rand() % 2 == 1) randDirX = 1;
		if (rand() % 2 == 1) randDirY = 1;
		e->getComponent<Collider>(ComponentType::Collider)->applyForce(b2Vec2((rand() % tomatoMaxSpeed_ * randDirX) + tomatoMinSpeed_,
			(rand() % tomatoMaxSpeed_ * randDirY) + tomatoMinSpeed_), b2Vec2(0, 0));
	}
}
