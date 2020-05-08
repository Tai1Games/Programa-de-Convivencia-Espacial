#include "StaplerWeapon.h"

StaplerWeapon::StaplerWeapon(int damage, BulletPool* pb) :ActionableWeapon(ComponentType::StaplerWeapon, WeaponID::Stapler, damage, 0),
bulletPool_(pb)
{
}

void StaplerWeapon::init()
{
	Weapon::init();
	currentAmo = CONST(int, "STAPLER_MAX_AMO");
}

void StaplerWeapon::action()
{
	if (currentAmo > 0) {
		b2Vec2 dir = currentHand_->getDir();
		int speed = CONST(double, "STAPLER_BULLET_SPEED");

		bulletPool_->addBullet(currentHand_->getPos(), { 1,1 }, { dir.x * speed + currentHand_->getVel().x,
			-dir.y * speed + currentHand_->getVel().y }, Resources::Staple,
			CONST(double, "STAPLER_BULLET_DAMAGE"), currentHand_->getPlayerId());

		currentAmo--;
	}
}
