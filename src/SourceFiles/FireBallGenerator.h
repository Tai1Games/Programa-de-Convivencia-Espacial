#pragma once
#include "Component.h"

class Collider;
class EntityManager;

using uint = unsigned int;
class FireBallGenerator :
	public Component
{
private:
	static Entity* generateFireball();
	EntityManager* manager_ = nullptr;
	Collider* col_ = nullptr;
	b2World* physicsWorld_ = nullptr;
	b2Vec2 pos_; //centro de la caldera, se cachea porque se supone estático
	b2Vec2 size_;//tamaño de la caldera, se cachea porque se supone estático
	uint nextShot_;
	uint minCd_;
	uint maxCd_;
	int minFireballs_, maxFireballs_;
	int fireballW_, fireballH_, fireballSpeed_;

public:
	FireBallGenerator(b2World* w) :Component(ComponentType::FireBallGenerator),physicsWorld_(w){}
	~FireBallGenerator() {};
	void init() override;
	void update() override;
};

