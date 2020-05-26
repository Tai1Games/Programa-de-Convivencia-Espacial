#pragma once
#include "Entity.h"

class Weapon;
class WeaponSpawner;

class TimedDespawn : public Component
{
private:
	int framesToDespawn_ = 0;
	int currentFrame_ = 0;
	bool activated = false;
	Weapon* weapon_ = nullptr;
	WeaponSpawner* weaponSpawner_ = nullptr;

public:
	TimedDespawn(int framesToDespawn) : Component(ComponentType::TimedDespawn) { framesToDespawn_ = framesToDespawn; }
	~TimedDespawn() {};
	void startTimer(Weapon* weapon);
	void setSpawner(WeaponSpawner* weaponSpawner) { weaponSpawner_ = weaponSpawner; }
	virtual void update();
};
