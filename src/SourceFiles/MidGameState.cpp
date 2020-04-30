#include "MidGameState.h"
#include "Collider.h"
#include "Resources.h"
#include "AnimatedViewer.h"
#include "Entity.h"
#include "SDL_Game.h"


MidGameState::~MidGameState()
{
	delete entityManager_;		entityManager_ = nullptr;
}

void MidGameState::init()
{
	entityManager_ = new EntityManager();

	int initPos = (CONST(int, "WINDOW_HEIGHT") / 2) - (-distanceBetweenRockets_ / 2 + (distanceBetweenRockets_ / 2 * numPlayers_));

	SDL_Rect textureRect;
	textureRect.x = textureRect.y = 0;
	textureRect.w = 34;
	textureRect.h = 34;

	for (int k = 0; k < numPlayers_; k++) {
		Entity* newRocket = entityManager_->addEntity();
		//We could move the rockets using only the Viewer, but this will make
		//the logic much much easier.

		AnimatedViewer* viewer = newRocket->addComponent<AnimatedViewer>(Resources::RoombaSpriteSheet, textureRect, 1, b2Vec2(startingXPosition_ + k * distanceGainedByPoint_, initPos + (distanceBetweenRockets_ * k) - 0.5), 1, 0);
		playerRockets_.push_back(viewer);
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
	if (currentFrame > framesUntilAnimationStart_ && !rocketAnimationStarted_) {
		rocketAnimationStarted_ = true;
		rocketXPositionObjective_ = playerRockets_[roundWinner_]->getPosUIElement().x + distanceGainedByPoint_;
	}
	if (rocketAnimationStarted_ && !rocketAnimationEnded_) {
		playerRockets_[roundWinner_]->setPosUIElement(b2Vec2(playerRockets_[roundWinner_]->getPosUIElement().x + distanceGainedPerFrame_, playerRockets_[roundWinner_]->getPosUIElement().y));

		if (playerRockets_[roundWinner_]->getPosUIElement().x > rocketXPositionObjective_) rocketAnimationEnded_ = true;
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
