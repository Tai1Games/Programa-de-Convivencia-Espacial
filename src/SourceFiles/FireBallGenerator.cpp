#include "FireBallGenerator.h"
#include "Collider.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Viewer.h"
#include "Resources.h"


void FireBallGenerator::init() {
	col_ = GETCMP1_(Collider);
	size_ = col_->getPos();

	//initialize constants
	minCd_ = CONST(int, "FBGEN_MIN_COOLDOWN");
	maxCd_ = CONST(int, "FBGEN_MAX_COOLDOWN");
	minFireballs_ = CONST(int, "FBGEN_MIN_FIREBALLS");
	maxFireballs_ = CONST(int, "FBGEN_MIN_FIREBALLS");

	manager_ = entity_->getEntityManager();
	nextShot_ = SDL_Game::instance()->getTime() + CONST(int,"FBGEN_INITIAL_OFFSET") 
		+ (rand() % maxCd_ + minCd_);
}

void FireBallGenerator::update() {
	//entity_->getEntityManager()->addEntity();
	uint actTime = SDL_Game::instance()->getTime();
	if (actTime > nextShot_) {
		int n = rand() % maxFireballs_ + minFireballs_;
		addFireball(n);
		nextShot_ = actTime + (rand() % maxCd_ + minCd_);
	}
}

void FireBallGenerator::addFireball(int n) {
	for (int i = 0; i < n; i++) {
		Entity* fBall = nullptr;
		if (fBall != nullptr) {
			fBall = entity_->getEntityManager()->addEntity();
			//Collider* col = fBall->addComponent<Collider>
			//	// x,  y,   width, height, density,friction, restitution, linearDrag, angularDrag,Layer, sensor
			//	(physicsWorld_, b2_dynamicBody, pos_.x, pos_.y, fireballW_, fireballH_, 1, 0.1, 0, 0, 0, Collider::CollisionLayer::Trigger, true);
			//fBall->addComponent<Viewer>(Resources::Fireball);
			//col->applyLinearImpulse(b2Vec2(rand() % 1, rand() % 1), b2Vec2(0, 0));
			//col->setUserData(fBall);
			//fBall = nullptr;
		}
	}


}