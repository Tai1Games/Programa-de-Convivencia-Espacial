#include "FireBallPool.h"
#include "Resources.h"
#include "Collider.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Viewer.h"
#include "ObjectFactory.h"

FireBallPool::FireBallPool() :fireballPool_([](Entity* e) {return e->isActive(); }) {};

void FireBallPool::init(EntityManager* eMan, b2World* physicsWorld) {
	fireballW_ = CONST(int, "FIREBALL_WIDTH");
	fireballH_ = CONST(int, "FIREBALL_HEIGTH");
	fireballSpeed_ = CONST(int, "FIREBALL_SPEED");

	vector<Entity*> fbPool = fireballPool_.getPool();
	for (Entity* e : fbPool) {
		ObjectFactory::makeFireball(e, eMan, physicsWorld, b2Vec2(0, 0), b2Vec2(fireballW_, fireballH_));
		e->setActive(false);
	}
}

void FireBallPool::addFireBall(b2Vec2 pos) {
	Entity* e = fireballPool_.getObj();
	if (e != nullptr) {
		e->setActive(true);
	}
}