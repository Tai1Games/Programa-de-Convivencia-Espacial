#include "FireBallPool.h"
#include "Resources.h"
#include "Collider.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Viewer.h"
#include "ObjectFactory.h"
#include "Fireball.h"

FireBallPool::FireBallPool() :fireballPool_([](Entity* e) {return e->isActive(); }) {};

void FireBallPool::init(EntityManager* eMan, b2World* physicsWorld) {

	vector<Entity*> fbPool = fireballPool_.getPool();
	for (Entity* e : fbPool) {
		ObjectFactory::makeFireball(e, eMan, physicsWorld, b2Vec2(0, 0));
		GETCMP2(e,Fireball)->setActive(false,b2Vec2(0,0));
	}
}

void FireBallPool::addFireBall(b2Vec2 pos, b2Vec2 impulse) {
	Entity* e = fireballPool_.getObj();
	if (e != nullptr) {
		GETCMP2(e, Fireball)->setActive(true, pos);
		GETCMP2(e, Collider)->applyLinearImpulse(impulse, b2Vec2(0, 0));

		cout << endl;
		cout << "---- BOLA ACTIVADA ----" << endl;
	}
}