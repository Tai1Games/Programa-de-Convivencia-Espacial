#include "StaplerWeapon.h"
#include "Viewer.h"
#include "TimedDespawn.h"

StaplerWeapon::StaplerWeapon(int damage, BulletPool* pb) : ActionableWeapon(ComponentType::StaplerWeapon, WeaponID::Stapler, damage, 0),
bulletPool_(pb)
{
}

void StaplerWeapon::init()
{
	Weapon::init();
	maxAmmo = CONST(int, "STAPLER_MAX_AMO");
	currentAmmo = maxAmmo;
	viewer_ = GETCMP1_(Viewer);
	collider_ = GETCMP1_(Collider);
	timedDespawn_ = GETCMP1_(TimedDespawn);
}

void StaplerWeapon::action()
{
	if (currentAmmo > 0) {
		b2Vec2 dir = currentHand_->getDir();
		int speed = CONST(double, "STAPLER_BULLET_SPEED");

		bulletPool_->addBullet(currentHand_->getPos(), { 1,1 }, { dir.x * speed + currentHand_->getVel().x,
			-dir.y * speed + currentHand_->getVel().y }, Resources::Staple,
			CONST(double, "STAPLER_BULLET_DAMAGE"), currentHand_->getPlayerId());

		currentAmmo--;
		if (currentAmmo == 0) timedDespawn_->startTimer(this);
	}
}

void StaplerWeapon::setActive(bool a, b2Vec2 pos)
{
	if (currentHand_ != nullptr) UnPickObject();
	currentAmmo = maxAmmo;
	entity_->setActive(a);
	viewer_->setDrawable(a);
	collider_->getBody()->SetEnabled(a);
	collider_->getBody()->SetTransform(pos, 0);
}
