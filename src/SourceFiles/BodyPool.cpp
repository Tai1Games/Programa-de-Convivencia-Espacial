#include "BodyPool.h"
#include "ObjectFactory.h"
#include "Viewer.h"

void BodyPool::init(EntityManager* eMan, b2World* physicsWorld, vector<Collider*>& collDeadBodies, vector<Entity*>& deadBodies) {
	vector<Entity*> pool = bodyPool_.getPool();
	for (Entity* e : pool) {
		ObjectFactory::makeDeadBody(e, eMan, physicsWorld, collDeadBodies, deadBodies, { 0,0 }, 0, { 0,0 }, 0);
		e->setActive(false);
	}
}

void BodyPool::addBody(b2Vec2 pos, float angle, b2Vec2 linearVelocity, float angularVelocity) {
	Entity* e = bodyPool_.getObj();
	Collider* bodycol = nullptr;
	bool recycledBody = false;
	if (e == nullptr) {
		recycledBody = true;
		e = bodyPool_.getPool()[oldestBody_];
	}
	else { e->setActive(true); }
	bodycol = e->getComponent<Collider>(ComponentType::Collider);
	bodycol->setTransform(b2Vec2(pos.x, pos.y), angle);
	bodycol->setLinearVelocity(linearVelocity);
	bodycol->setAngularVelocity(angularVelocity);
	if (recycledBody) {
		oldestBody_++;
		if (oldestBody_ >= BODY_POOL_SIZE) oldestBody_ = 0;
	}
}