#include "ConfettiPool.h"
#include "ConfettiWeapon.h"
#include "ObjectFactory.h"

ConfettiPool::ConfettiPool() : confettiPool_([](Entity* e) {return e->isActive(); }) {};

void ConfettiPool::init(EntityManager* eMan, b2World* physicsWorld, GameMode* gM)
{	
	b2Vec2 confettiSize = b2Vec2(CONST(float, "CONFETTI_W_PHYSICS"), CONST(float, "CONFETTI_H_PHYSICS"));
	vector<Entity*> confettiPoolVector= confettiPool_.getPool();
	for (Entity* e : confettiPoolVector) {
		e = ObjectFactory::makeConfetti(e, eMan, physicsWorld, b2Vec2(0, 0), confettiSize, gM);
		e->getComponent<ConfettiWeapon>(ComponentType::Weapon)->setActive(false);
	}
}

void ConfettiPool::addConfetti(b2Vec2 pos)
{
	Entity* e = confettiPool_.getObj();
	if (e != nullptr) {
		ConfettiWeapon* confetti = e->getComponent<ConfettiWeapon>(ComponentType::Weapon);
		confetti->setActive(true, pos);
	}
}
