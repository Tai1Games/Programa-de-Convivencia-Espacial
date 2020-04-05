#pragma once
#include "Component.h"
#include "Texture.h"
#include "Collider.h"
#include "PlayerData.h"
#include "Weapon.h"
#include "Constants.h"

class Hands : public Component
{
private:
	b2Vec2 pos_ = b2Vec2(0,0);
	b2Vec2 dir_ = b2Vec2(0,0);
	Texture* tex_ = nullptr;
	Collider* collider_ = nullptr;
	int textureId_ = 0;
	PlayerData* playerData_ = nullptr;
	WeaponID currentWeaponID_ = NoWeapon;
	InputHandler* ih_ = nullptr;
	float angle_ = 0;
	bool onFlipped_ = false;
	Weapon* currentWeapon_ = nullptr;
protected:
public:
	Hands(int textureId, WeaponID wId = NoWeapon);
	~Hands() {};
	virtual void init() override;
	virtual void draw() const;
	virtual void handleInput();
	virtual void update() override;
	void setWeapon(WeaponID wId, Weapon* w);
	int getPlayerId() { return playerData_->getPlayerNumber(); }
	b2Vec2 getPos() { return pos_; }
	b2Vec2 getDir() { return dir_; }
	float getAngle() { return angle_; }
	Weapon* getWeapon() { return currentWeapon_; }
	WeaponID getWeaponID() { return currentWeaponID_; }
};

