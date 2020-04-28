#include "RocketLogic.h"
#include "Viewer.h"
#include "Entity.h"
#include "MidGameState.h"

void RocketLogic::init()
{
	rocketViewer_ = GETCMP1_(Viewer);
	rocketColl_ = GETCMP1_(Collider);
}

void RocketLogic::update()
{
	if (animationStarted_) {
		rocketViewer_->draw();
		if (rocketColl_->getPos().y >= YPositionObjective_) {
			gameState_->rocketReachedDestination();
			rocketColl_->setLinearVelocity(b2Vec2(0, 0));
		}
	}
}

void RocketLogic::startAnimation()
{
	animationStarted_ = true;
	rocketColl_->applyLinearImpulse(b2Vec2(100, 100), b2Vec2(0, 0));
	YPositionObjective_ = rocketColl_->getPos().y + 2.5;
}
