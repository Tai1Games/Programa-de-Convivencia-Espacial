#include "WeaponSpawner.h"
#include "WeaponFactory.h"
#include "TimedDespawn.h"
#include "Constants.h"

void WeaponSpawner::spawnWeapon(){
	Entity* e = WeaponFactory::makeLowTierWeapon(eMan_, b2world_, pos_, confettiPool_);

	e->getComponent<TimedDespawn>(ComponentType::TimedDespawn)->setSpawner(this);
}

void WeaponSpawner::onWeaponDespawned()
{
	activated_ = true;
	
	frameToSpawn_ = currentFrame_ + framesBetweenSpawns_;
}

void WeaponSpawner::init() {
	framesBetweenSpawns_ = CONST(int, "WEAPON_SPAWN_TIME_TO_SPAWN") * FRAMES_PER_SECOND;
}

void WeaponSpawner::update() {
	if (activated_) {
		currentFrame_++;
		if (currentFrame_ >= frameToSpawn_) {
			spawnWeapon();

			activated_ = false;
		}
	}
}
