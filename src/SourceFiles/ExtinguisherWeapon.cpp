#include "ExtinguisherWeapon.h"
#include "ParticleEmitter.h"
#include "Hands.h"

ExtinguisherWeapon::ExtinguisherWeapon(WeaponID wId, int dmg, int impctDmg) : Weapon(wId, dmg, impctDmg),
impulse_(0.0), framesSinceActivation_(0), cooldown_(0), activated(false),
PIXELS_PER_METER(0), WINDOW_HEIGHT(0), emitter_(nullptr) {}

void ExtinguisherWeapon::init() {
	Weapon::init();

	emitter_ = GETCMP1_(ParticleEmitter);
	impulse_ = CONST(float, "EXTINGUISHER_IMPULSE");
	cooldown_ = CONST(int, "EXTINGUISHER_COOLDOWN_FRAMES");
	PIXELS_PER_METER = CONST(float, "PIXELS_PER_METER");
	WINDOW_HEIGHT = CONST(int, "WINDOW_HEIGHT");
}

void ExtinguisherWeapon::update() {
	if (activated) {
		framesSinceActivation_++;
		if (framesSinceActivation_ >= cooldown_) {
			framesSinceActivation_ = 0;
			activated = false;
		}
	}

	Weapon::update();
}

void ExtinguisherWeapon::Action() {
	if (!activated) {
		b2Vec2 handDirection = currentHand_->getDir();
		Collider* playerCollider = currentHand_->getEntity()->getComponent<Collider>(ComponentType::Collider);
		emitter_->setPositionCollider(playerCollider);
		emitter_->setDirection({ handDirection.x, handDirection.y });
		emitter_->PlayStop();
		b2Vec2 impulse = { -handDirection.x,handDirection.y };
		impulse *= (impulse_);
		playerCollider->applyLinearImpulse(impulse, { 0, 0 });

		activated = true;
	}
}

void ExtinguisherWeapon::UnPickObject() {
	emitter_->setPositionCollider(GETCMP1_(Collider));
	Weapon::UnPickObject();
}