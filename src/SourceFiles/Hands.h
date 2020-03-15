#pragma once
#include "Component.h"
#include "Texture.h"
#include "Collider.h"
#include "Weapon.h"
class Hands : public Component
{
private:
	b2Vec2 pos_ = b2Vec2(0,0);
	b2Vec2 dir_ = b2Vec2(0,0);
	double bodyOffset_ = 130;
	Texture* tex_ = nullptr;
	Collider* collider_ = nullptr;
	int textureId_ = 0;
	int playerID_ = -1;
	WeaponID currentWeapon_ = NoWeapon;
	InputHandler* ih_ = nullptr;
	float angle_ = 0;
	bool onFlipped_ = false;
protected:
public:
	Hands(int playerID, int textureId, WeaponID wId = NoWeapon);
	~Hands() {};
	virtual void init() override;
	virtual void draw() const;
	virtual void update() override;
	void setWeapon(WeaponID wId);
	int getPlayerId() { return playerID_; }
	b2Vec2 getPos() { return pos_; }
	b2Vec2 getDir() { return dir_; }
	float getAngle() { return angle_; }
};

