#include "MidGameState.h"
#include "RocketLogic.h"
#include "Collider.h"
#include "Resources.h"
#include "Viewer.h"
#include "Entity.h"
#include "SDL_Game.h"


MidGameState::~MidGameState()
{
	delete entityManager_;		entityManager_ = nullptr;
	delete b2World_;		    b2World_ = nullptr;
}

void MidGameState::init()
{
	entityManager_ = new EntityManager();
	b2World_ = new b2World(b2Vec2(0, 0));

	//int initPos = CONST(int, "WINDOW_WIDTH") / CONST(double, "PIXELS_PER_METER") - distanceBetweenRockets_ / 2 + distanceBetweenRockets_ * numPlayers_;
	int initPos = (CONST(int, "WINDOW_WIDTH") / 2 / CONST(double, "PIXELS_PER_METER")) - (-distanceBetweenRockets_ / 2 + (distanceBetweenRockets_ / 2 * numPlayers_));
	for (int k = 0; k < numPlayers_; k++) {
		Entity* newRocket = entityManager_->addEntity();
		//We could move the rockets using only the Viewer, but this will make
		//the logic much much easier.

		newRocket->addComponent<Collider>(b2World_, b2_dynamicBody, initPos + (distanceBetweenRockets_ * k) - 0.5,  startingYPosition_ + distanceGainedByPoint_ * k, 1, 1, 1, 1, 1, 1, Collider::CollisionLayer::UnInteractableObject, true);
		newRocket->addComponent<Viewer>(Resources::Tinky);
		RocketLogic* rL = newRocket->addComponent<RocketLogic>(k, this);
		playerRockets.push_back(rL);
	}
}

void MidGameState::render()
{
	GameState::render();
}

void MidGameState::update()
{
	GameState::update();
	currentFrame++;

	if (currentFrame > framesUntilAnimationStart_) {
		rocketAnimationStarted = true;
		playerRockets[roundWinner_]->startAnimation();
	}
}

void MidGameState::handleInput()
{
	GameState::handleInput();
}

void MidGameState::rocketReachedDestination()
{
	cout << "haha yes";
}
