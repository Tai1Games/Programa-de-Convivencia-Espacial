#include "ConfettiPool.h"
#include "ConfettiWeapon.h"
#include "ObjectFactory.h"

ConfettiPool::ConfettiPool() : confettiPool_([](Entity* e) {return e->isActive(); }) {};

void ConfettiPool::init(EntityManager* eMan, b2World* physicsWorld)
{	
	b2Vec2 confettiSize = b2Vec2(CONST(float, "CONFETTI_X"), CONST(float, "CONFETTI_Y"));
	vector<Entity*> tomatoPool = confettiPool_.getPool();
	for (Entity* e : tomatoPool) {
		e = ObjectFactory::makeConfetti(e, eMan, physicsWorld, b2Vec2(0, 0), confettiSize);
		e->getComponent<ConfettiWeapon>(ComponentType::ConfettiWeapon)->setActive(false);
	}
}

void ConfettiPool::addConfetti(b2Vec2 pos)
{
	Entity* e = confettiPool_.getObj();
	if (e != nullptr) {
		ConfettiWeapon* confetti = e->getComponent<ConfettiWeapon>(ComponentType::ConfettiWeapon);
		confetti->setActive(true, pos);
	}
}