#include "Treadmill.h"
#include "Collision.h"

void Treadmill::init() {
	frame_ = 0;
	myView_ = GETCMP1_(Viewer);
	spinSpeed_ = CONST(float, "TREADMILL_SPIN_SPEED");
	launchSpeed_ = CONST(float, "TREADMILL_LAUNCH_SPEED");
	speedUp_ = CONST(float, "TREADMILL_SPIN_SPEED_UP");
	animationSpeed_ = CONST(int, "TREADMILL_ANIMATION_SPEED");
	totalFrames_ = CONST(int, "TREADMILL_ANIMATION_FRAMES");
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
	//animation
	int pos = 82 * (frame_ / animationSpeed_);
	myView_->setClip(SDL_Rect{ pos, 0 ,82,46 });
	frame_++;
	if (frame_ / animationSpeed_ == totalFrames_) { //ha terminado la animacion 
		myView_->setClip(SDL_Rect{ 0, 0, 82,46 });
		frame_ = 0;
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