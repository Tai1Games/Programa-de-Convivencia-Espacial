#include "ExtinguisherWeapon.h"
#include "ParticleEmitter.h"
#include "Hands.h"

ExtinguisherWeapon::ExtinguisherWeapon(WeaponID wId, int impctDmg, int cooldownFrames, int impctForce) : 
	ActionableWeapon(wId, impctDmg, cooldownFrames, impctForce),
impulse_(0.0), PIXELS_PER_METER(0), WINDOW_HEIGHT(0), emitter_(nullptr) {}

void ExtinguisherWeapon::init() {
	Weapon::init();

	emitter_ = GETCMP1_(ParticleEmitter);
	impulse_ = CONST(float, "EXTINGUISHER_IMPULSE");
	PIXELS_PER_METER = CONST(float, "PIXELS_PER_METER");
	WINDOW_HEIGHT = CONST(int, "WINDOW_HEIGHT");
	armLength_ = CONST(float, "EXTINGUISHER_ARM_LENGTH");
}

void ExtinguisherWeapon::action() {
	if (!beenActivated_) {
		b2Vec2 handDirection = currentHand_->getDir();
		Collider* playerCollider = currentHand_->getEntity()->getComponent<Collider>(ComponentType::Collider);
		emitter_->setPositionCollider(playerCollider);
		emitter_->setDirection({ handDirection.x, handDirection.y });
		emitter_->PlayStop();
		b2Vec2 impulse = { -handDirection.x,handDirection.y };
		impulse *= (impulse_);
		playerCollider->applyLinearImpulse(impulse, { 0, 0 });

		beenActivated_ = true;
	}
}

void ExtinguisherWeapon::UnPickObject() {
	emitter_->setPositionCollider(GETCMP1_(Collider));
	Weapon::UnPickObject();
	emitter_->PlayStop();
}