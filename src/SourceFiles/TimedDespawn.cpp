#include "TimedDespawn.h"
#include "Weapon.h"
#include "WeaponSpawner.h"

void TimedDespawn::startTimer(Weapon* weapon)
{
	weapon_ = weapon;
	activated = true;
}

void TimedDespawn::update()
{
	if (activated) {
		currentFrame_++;
		if (currentFrame_ >= framesToDespawn_) {
			weapon_->setActive(false);
			
			//Security measures.
			activated = false;
			currentFrame_ = 0;

			if (weaponSpawner_) {
				weaponSpawner_->onWeaponDespawned();
			}
		}
	}
}
