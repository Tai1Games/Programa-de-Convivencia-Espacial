#pragma once

#include "SpawnTree.h"
#include "EntityManager.h"

class TomatoTree : public SpawnTree {
private:
	double objectW_, objectH_;
	virtual void SpawnObject() override;
	EntityManager* eMan_ = nullptr;
	b2World* pWorld_ = nullptr;
public:
	TomatoTree(Texture* objectText, EntityManager* eMan, b2World* pWorld) : SpawnTree(objectText), eMan_(eMan), pWorld_(pWorld) {}
	virtual void init() override;
};
