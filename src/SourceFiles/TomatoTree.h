/*#pragma once

#include "SpawnTree.h"
#include "EntityManager.h"
#include "TomatoPool.h"

class TomatoTree : public SpawnTree {
private:
	
	virtual void SpawnObject() override;
	
public:
	TomatoTree(Texture* objectText, EntityManager* eMan, b2World* pWorld, TomatoPool* pool) : 
		SpawnTree(objectText), eMan_(eMan), pWorld_(pWorld), pool_(pool) {}
	virtual void init() override;
};*/
