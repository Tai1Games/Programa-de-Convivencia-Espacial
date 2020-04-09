#pragma once
#include "Component.h"
#include "ObjectPool.h"

class Collider;
class EntityManager;

using uint = unsigned int;
class FireBallGenerator :
	public Component
{
private:
	EntityManager* manager_ = nullptr;
	Collider* col_ = nullptr;
	b2World* physicsWorld_ = nullptr;
	b2Vec2 pos_; //centro de la caldera, se cachea porque se supone estático
	b2Vec2 size_;//tamaño de la caldera, se cachea porque se supone estático
	uint nextShot_;
	uint minCd_;
	uint maxCd_;
	int minFireballs_, maxFireballs_;
	void addFireball(int num = 1);

public:
	FireBallGenerator(b2World* w) :Component(ComponentType::FireBallGenerator),physicsWorld_(w){}
	~FireBallGenerator() {};
	void init() override;
	void update() override;

};

