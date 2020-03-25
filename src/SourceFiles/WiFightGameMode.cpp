#include "WiFightGameMode.h"

void WiFightGameMode::init(PlayState* game)
{
	GameMode::init(game);
	playerProgress_.reserve(players_.size());
	for (int k = 0; k < players_.size(); k++) {
		playerProgress_.push_back(0);
	}

	router = state_->getEntityManager()->addEntity();
	Collider* collRouter = router->addComponent<Collider>(state_->getPhysicsWorld(), b2_dynamicBody, 5, 5, 1, 1, 0.01, 0, 1, 0, 0, Collider::CollisionLayer::UnInteractableObject, false);
	collRouter->setUserData(router);
	router->addComponent<Viewer>();

	collRouter->applyForce(b2Vec2(5, -5), b2Vec2(0,0));
}