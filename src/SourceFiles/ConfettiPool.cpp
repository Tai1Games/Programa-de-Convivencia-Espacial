#include "ConfettiPool.h"
#include "ConfettiWeapon.h"
#include "WeaponFactory.h"

ConfettiPool::ConfettiPool() : confettiPool_([](Entity* e) {return e->isActive(); }) {};

void ConfettiPool::init(EntityManager* eMan, b2World* physicsWorld)
{	
	b2Vec2 confettiSize = b2Vec2(CONST(float, "CONFETTI_X"), CONST(float, "CONFETTI_Y"));
	vector<Entity*> confettiPoolVector= confettiPool_.getPool();
	for (Entity* e : confettiPoolVector) {
		e = WeaponFactory::makeConfetti(e, eMan, physicsWorld, b2Vec2(0, 0), confettiSize);
		e->getComponent<ConfettiWeapon>(ComponentType::Weapon)->setActive(false);
	}
}

Entity* ConfettiPool::addConfetti(b2Vec2 pos)
{
	Entity* e = confettiPool_.getObj();
	if (e != nullptr) {
		ConfettiWeapon* confetti = e->getComponent<ConfettiWeapon>(ComponentType::Weapon);
		confetti->setActive(true, pos);
	}
	return e;
}
