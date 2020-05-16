#include "Treadmill.h"
#include "Collision.h"

void Treadmill::init() {
	spinSpeed_ = CONST(float, "TREADMILL_SPIN_SPEED");
	launchSpeed_ = CONST(float, "TREADMILL_LAUNCH_SPEED");
	speedUp_ = CONST(float, "TREADMILL_SPIN_SPEED_UP");
}

void Treadmill::update() {
	//speed up
	spinSpeed_ += speedUp_;
	myCol_->getBody()->SetAngularVelocity(spinSpeed_);
	//launch objects
	float angle = myCol_->getAngle();
	for (b2Body* b : objectsInside_) {
		b->ApplyForce(b2Vec2(launchSpeed_ * cos(angle), launchSpeed_ * sin(angle)), b->GetPosition(), true);
	}
}

void Treadmill::onCollisionEnter(Collision* c) {
	objectsInside_.push_back(c->hitFixture->GetBody());
}

void Treadmill::onCollisionExit(Collision* c) {
	b2Body* lost = c->hitFixture->GetBody();
	vector<b2Body*>::iterator it = std::find(objectsInside_.begin(), objectsInside_.end(), lost);
	objectsInside_.erase(it);
}