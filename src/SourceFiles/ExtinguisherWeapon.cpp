#include "ExtinguisherWeapon.h"
#include "ParticleEmitter.h"
#include "Hands.h"

void ExtinguisherWeapon::init() {
	Weapon::init();

	emitter_ = GETCMP1_(ParticleEmitter);
	impulse_ = CONST(float, "EXTINGUISHER_IMPULSE");
	PIXELS_PER_METER = CONST(float, "PIXELS_PER_METER");
	WINDOW_HEIGHT = CONST(int, "WINDOW_HEIGHT");
}

void ExtinguisherWeapon::update() {

}

void ExtinguisherWeapon::Action() {
	b2Vec2 handDirection = currentHand_->getDir();
	Collider* playerCollider = currentHand_->getEntity()->getComponent<Collider>(ComponentType::Collider);
	emitter_->setDirection({ handDirection.x, handDirection.y });
	emitter_->setPosition({ playerCollider->getPos().x * PIXELS_PER_METER, (playerCollider->getPos().y * PIXELS_PER_METER) * -1 + WINDOW_HEIGHT });
	emitter_->PlayStop();

	b2Vec2 impulse = { -handDirection.x,handDirection.y };
	impulse *= (impulse_);
	playerCollider->applyLinearImpulse(impulse, { 0, 0 });
}