#pragma once
#include "Component.h"
#include "FireBallPool.h"

class Collider;
class EntityManager;
class ParticleEmitter;

using uint = unsigned int;
class FireBallGenerator :
	public Component
{
private:
	EntityManager* manager_ = nullptr;
	Collider* col_ = nullptr;
	ParticleEmitter* particleEmitter_ = nullptr;
	b2World* physicsWorld_ = nullptr;
	FireBallPool fbPool_;
	b2Vec2 pos_; //centro de la caldera, se cachea porque se supone estático
	b2Vec2 size_;//tamaño de la caldera, se cachea porque se supone estático
	uint nextShot_;
	uint minCd_;
	uint maxCd_;
	uint cdVariability;
	uint limitMinCd_;
	uint limitMaxCd_;
	uint cdTimeChange_;
	
	int minFireballs_, maxFireballs_;
	int fireballSpeed_;
	int particleGenOddsModifier_;
	double radius;

	void addFireball(int num = 1);

public:
	FireBallGenerator(b2World* w) :
		Component(ComponentType::FireBallGenerator),
		physicsWorld_(w){}
	~FireBallGenerator() {};
	void init() override;
	void update() override;
	void onButtonAction(bool inc_dec);
};

