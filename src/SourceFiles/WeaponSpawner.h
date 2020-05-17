#pragma once
#include "Entity.h"
#include "Vector2D.h"

class ConfettiPool;
class StaplerPool;
class BulletPool;
class Weapon;

class WeaponSpawner : public Component
{
private:
	EntityManager* eMan_ = nullptr;
	b2World* b2world_ = nullptr;
	b2Vec2 pos_;
	ConfettiPool* confettiPool_ = nullptr;
	StaplerPool* staplerPool_ = nullptr;
	BulletPool* bulletPool_ = nullptr;
	Weapon* weaponOnGame_ = nullptr;
	int currentFrame_ = 0;
	int frameToSpawn_ = 0; //Frame in which a weapon will spawn
	bool activated_ = true;

	int framesBetweenSpawns_ = 0; //initiated at init();
public:
	WeaponSpawner(b2Vec2 pos, EntityManager* eMan, b2World* b2World, ConfettiPool* confettiPool, StaplerPool* staplerPool, BulletPool* bulletPool) : 
		Component(ComponentType::WeaponSpawner) { pos_ = pos; eMan_ = eMan; b2world_ = b2World; confettiPool_ = confettiPool; staplerPool_ = staplerPool; bulletPool_ = bulletPool; }
	~WeaponSpawner() {};

	void spawnWeapon();
	void onWeaponDespawned(); //This is called when a weapon loses ammo and despawns from the scene.
	virtual void update();
	virtual void init();
};

