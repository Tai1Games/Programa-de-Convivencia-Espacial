#pragma once

#include "Component.h"
#include "Entity.h"
#include "Texture.h"
#include "checkML.h"

class SpawnTree : public Component {
private:
protected:
	double spawnTime_ = 0;
	int pixPerM_ = 0;
	int objectW_, objectH_;
	int currentW_ = 0, currentH_ = 0;
	double timer_ = 0;
	double sPerFrame_ = 0;
	Texture* objectTex_ = nullptr;
	virtual void SpawnObject() = 0;
	b2Vec2 spawnPos_;
public:
	SpawnTree(Texture* objectText): Component(ComponentType::SpawnTree), objectTex_(objectText) {}
	~SpawnTree() {}
	virtual void init() override;
	virtual void update() override;
	virtual void draw() const override;
};