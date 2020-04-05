#include "MeleeWeapon.h"

void MeleeWeapon::update()
{
	
}

void MeleeWeapon::Action()
{
	//Calculo del daño de la chancla
	int damage = playerInfo_[currentHand_->getPlayerId()].playerHealth->getHealthMax() - playerInfo_[currentHand_->getPlayerId()].playerHealth->getHealth() + 1;

	cout << "Golpeaste con una fuerza de " << damage << " al contrincante" << endl;

}
