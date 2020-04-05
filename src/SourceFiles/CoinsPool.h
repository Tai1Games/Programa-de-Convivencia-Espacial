#pragma once
#include "ObjectPool.h"
#include "Entity.h"
#include "SDL_Game.h"
#include "ObjectFactory.h"
#include "EntityManager.h"
#include "b2_world.h"
#include "Viewer.h"
#include "Coin.h"
#include "b2_polygon_shape.h"

class CoinsPool {
public:
	CoinsPool();
	~CoinsPool() {};
	void init(EntityManager* eMan, b2World* physicsWorld);

	void addCoin(b2Vec2 pos, int val = 1);
private:
	ObjectPool<Entity, 20> coinsPool_;
};

