#pragma once
#include "Component.h"
#include "FireBallPool.h"

class Collider;
class EntityManager;
class ParticleEmitter;
class AnimatedViewer;

using uint = unsigned int;
class FireBallGenerator :
	public Component
{
private:
	EntityManager* manager_ = nullptr;
	Collider* col_ = nullptr;
	ParticleEmitter* particleEmitter_ = nullptr;
	AnimatedViewer* boilerViewer_;
	b2World* physicsWorld_ = nullptr;
	FireBallPool fbPool_;
	b2Vec2 pos_; //centro de la caldera, se cachea porque se supone est�tico
	b2Vec2 size_;//tama�o de la caldera, se cachea porque se supone est�tico

	//Fireballs spawn
	uint nextShot_;
	uint minCd_;
	uint maxCd_;
	uint cdVariability;
	uint limitMinCd_;
	uint limitMaxCd_;
	uint cdTimeChange_;
	int minFireballs_, maxFireballs_;
	int fireballSpeed_;

	double radius;

	//Smoke particle generation
	int particleGenOddsModifier_;
	
	//Boiler shake
	int currentFrame = 0;
	int framesForNextShake = 0;
	int framesBetweenShakes_ = 0;
	int incrementFramesShakeFreq_ = 0;
	int minFramesShake = 0;
	int maxFramesShake = 0;
	int shakeOffsetX_ = 0;
	int shakeOffsetY_ = 0;

	//Boiler animation
	int animationSpeed_ = 0;
	int animationSpeedModifier_ = 0;

	bool activated_ = false;

	void addFireball(int num = 1);

public:
	FireBallGenerator(b2World* w) :
		Component(ComponentType::FireBallGenerator),
		physicsWorld_(w){}
	~FireBallGenerator() {};
	void init() override;
	void update() override;
	void onButtonAction(bool inc_dec);
	void activate(bool active) { activated_ = active; }
};

