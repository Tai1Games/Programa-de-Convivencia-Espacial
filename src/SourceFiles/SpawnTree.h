#pragma once

#include "Component.h"
#include "Entity.h"
#include "Texture.h"
#include "checkML.h"
#include "WeaponPool.h"

class SpawnTree : public Component {
private:
protected:
	double spawnTime_ = 0;
	int pixPerM_ = 0;
	double objectW_ = 0, objectH_ = 0;
	double currentW_ = 0, currentH_ = 0;
	double timer_ = 0;
	double sPerFrame_ = 0;
	Texture* objectTex_ = nullptr;
	b2Vec2 renderSpawnPos_;
	b2Vec2 physicsSpawnPos_;
	EntityManager* eMan_ = nullptr;
	WeaponPool* pool_ = nullptr;
	b2World* pWorld_ = nullptr;

	void SpawnObject();
public:
	SpawnTree(Texture* objectText, double objectW, double objectH, WeaponPool* pool, EntityManager* eMan, b2World* pWorld);
	~SpawnTree() {}
	virtual void init() override;
	virtual void update() override;
	virtual void draw() const override;
};