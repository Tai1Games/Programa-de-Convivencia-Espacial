#pragma once
#include "Component.h"
#include "Texture.h"
#include "Collider.h"
#include "PlayerData.h"
#include "Weapon.h"
#include "Constants.h"
#include "checkML.h"

class AnimatedViewer;

class Hands : public Component
{
private:
	b2Vec2 handPos_ = b2Vec2(0, 0);
	b2Vec2 pos_ = b2Vec2(0, 0);
	b2Vec2 dir_ = b2Vec2(0, 0);

	double armLengthPhysics_ = 0;
	double handSize_ = 0;

	Texture* tex_ = nullptr;
	Collider* collider_ = nullptr;
	int textureId_ = 0;
	PlayerData* playerData_ = nullptr;
	WeaponID currentWeaponID_ = NoWeapon;
	InputBinder* ib_ = nullptr;
	float angle_ = 0;
	SDL_RendererFlip Flipped_ = SDL_FLIP_NONE; //si las manos estan o no flipeadas
	Weapon* currentWeapon_ = nullptr;
	AnimatedViewer* viewerHands_ = nullptr;

public:
	Hands(int textureId, WeaponID wId = NoWeapon);
	~Hands() {};
	virtual void init() override;
	virtual void draw() const;
	virtual void handleInput();
	virtual void update() override;
	void setWeapon(WeaponID wId, Weapon* w);
	int getPlayerId() { return playerData_->getPlayerNumber(); }
	Collider* getColHands_() { return collider_; }
	b2Vec2 getPos() { return pos_; }
	b2Vec2 getDir() { return dir_; }
	b2Vec2 getVel() { return collider_->getLinearVelocity(); }
	float getAngle() { return angle_; }
	Weapon* getWeapon() { return currentWeapon_; }
	WeaponID getWeaponID() { return currentWeaponID_; }
	b2Vec2 getPointerPos() { return handPos_; };
	double getArmLengthPhysics() { return armLengthPhysics_; }
};

