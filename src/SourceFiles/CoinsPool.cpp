#include "CoinsPool.h"
#include "Coin.h"
#include "ObjectFactory.h"
#include "Entity.h"

CoinsPool::CoinsPool() : coinsPool_([](Entity* e) { return e->isActive(); }) {};

void CoinsPool::init(EntityManager* eMan, b2World* physicsWorld) {
	vector<Entity*> coinPool = coinsPool_.getPool();
	for (Entity* e : coinPool) {
		ObjectFactory::makeCoin(e, eMan, physicsWorld, b2Vec2(0, 0), 1);
		e->getComponent<Coin>(ComponentType::Coin)->setActive(false);
	}
	coinMaxSpeed_ = CONST(int, "COIN_MAX_SPEED");
}

void CoinsPool::addCoin(b2Vec2 pos, int player, int val) {
	Entity* e = coinsPool_.getObj();
	if (e != nullptr) {
		Coin* coin = e->getComponent<Coin>(ComponentType::Coin);
		coin->setActive(true, player, pos, val);
		int randDirX = -1;
		int randDirY = -1;
		if (rand() % 2 == 1) randDirX = 1;
		if (rand() % 2 == 1) randDirY = 1;
		e->getComponent<Collider>(ComponentType::Collider)->applyForce(b2Vec2(rand() % coinMaxSpeed_ * randDirX, rand() % coinMaxSpeed_ * randDirY), b2Vec2(0,0));
	}
}
