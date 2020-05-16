#pragma once
#include "Entity.h"
#include "Vector2D.h"

class WeaponSpawner : public Component
{
private:
	Vector2D pos_;
	int tier_; //0 = low, 1 = mid, 2 = high

	int currentFrame_ = 0;
	int framesUntilSpawn_ = 0; //Frames until next rnd weapon spawn
	bool activated_ = false;
public:
	WeaponSpawner(Vector2D pos) : Component(ComponentType::WeaponSpawner) { pos_ = pos; }
	~WeaponSpawner() {};

	void spawnWeapon();
	void onWeaponDespawned(); //This is called when a weapon loses ammo and despawns from the scene.
	virtual void update();
};

