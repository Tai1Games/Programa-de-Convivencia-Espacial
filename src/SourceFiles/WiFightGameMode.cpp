#include "WiFightGameMode.h"

void WiFightGameMode::init(PlayState* game)
{
	GameMode::init(game);
	playerProgress_.reserve(players_.size());
	for (int k = 0; k < players_.size(); k++) {
		playerProgress_.push_back(0);
	}

	router = state_->getEntityManager()->addEntity();
	Collider* collRouter = router->addComponent<Collider>(state_->getPhysicsWorld(), b2_dynamicBody, 5, 5, 1, 1, 0.01, 0, 0.99, 0, 0, Collider::CollisionLayer::UnInteractableObject, false);
	collRouter->createCircularFixture(5, 1, 0, 0, Collider::CollisionLayer::Trigger, true);
	collRouter->setUserData(router);
	router->addComponent<Viewer>();
	router->addComponent<RouterLogic>(this);

	collRouter->applyForce(b2Vec2(10, 0), b2Vec2(0, 0));
}

void WiFightGameMode::addPoints(int player, double sumPoints)
{
	playerProgress_[player] += sumPoints;
	cout << "Player " << player << " progress: " << playerProgress_[player] << endl;
	if (playerProgress_[player] >= CONST(int, "POINTS_TO_WIN")) {
		cout << "Player " << player << " won!" << endl;
		winner = players_[player];
		roundFinished_ = true;
	}
}
