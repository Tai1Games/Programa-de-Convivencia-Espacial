#include "MeleeWeapon.h"
#include "Hands.h"

MeleeWeapon::MeleeWeapon(WeaponID wId, int impactDmg, int dmg, int cooldownFrames) : ActionableWeapon(ComponentType::MeleeWeapon, wId, impactDamage_, cooldownFrames),
damage_(dmg){};

void MeleeWeapon::action() {
	//if (weaponType_ == WeaponID::Slipper) {

	//	if (playersInsideRange_.size() > 0) {
	//		//Calculo del daño de la chancla
	//		if (playerInfo_[currentHand_->getPlayerId()].playerHealth) {
	//			damage_ = playerInfo_[currentHand_->getPlayerId()].playerHealth->getHealthMax() - playerInfo_[currentHand_->getPlayerId()].playerHealth->getHealth() + 1;
	//		}
	//		else damage_ = calculateCoinsDropped(playerInfo_[currentHand_->getPlayerId()].playerWallet->getCoins());

	//		//cout << "Golpeaste con una fuerza de " << damage_ << " al contrincante" << endl;
	//		vector<EnemyData>::iterator it = playersInsideRange_.begin();
	//		while (it != playersInsideRange_.end()) {

	//			//Patear al enemigo
	//			Health* auxHe = it->enemy->getComponent<Health>(ComponentType::Health);
	//			Wallet* auxWa = it->enemy->getComponent<Wallet>(ComponentType::Wallet);

	//			Collider* auxCo = it->enemy->getComponent<Collider>(ComponentType::Collider);

	//			b2Vec2 knockback = auxCo->getPos() - mainCollider_->getPos();
	//			knockback.Normalize();
	//			knockback *= CONST(double, "WEAPON_MELEE_KNOCKBACK");

	//			auxCo->applyLinearImpulse(knockback, b2Vec2(0, 1));
	//			if (auxHe) auxHe->subtractLife(damage_);
	//			else auxWa->dropCoins(damage_, it->enemy->getComponent<PlayerData>(ComponentType::PlayerData)->getPlayerNumber());

	//			++it;
	//		}
	//		//Activamos el cooldown
	//		coolDown = true;
	//		actionTime = 0;

	//		//Tras aplicar el golpe a tol que estén en rango limpiamos el vector
	//		playersInsideRange_.clear();
	//	}
	//}
}