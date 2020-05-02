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

	//Fondo del modo	
	fondo= SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::RocketRoom);

	int initPos = (CONST(int, "WINDOW_HEIGHT") / 2) - (-distanceBetweenRockets_ / 2 + (distanceBetweenRockets_ / 2 * numPlayers_));

	SDL_Rect rocketRect;
	rocketRect.x = rocketRect.y = 0;
	rocketRect.w = 160;
	rocketRect.h = 76;

	SDL_Rect stationRect;
	stationRect.x = 0;
	stationRect.y = 0;
	stationRect.w = 300;
	stationRect.h = 150;

	Entity* spaceStation = entityManager_->addEntity();
	spaceStationViewer_ = spaceStation->addComponent<AnimatedViewer>(Resources::SpaceStation, stationRect, 3, b2Vec2(CONST(int, "WINDOW_WIDTH") / 2 - spaceStationWidht_ / 2, CONST(int, "WINDOW_HEIGHT") / 2 - spaceStationHeight_ / 2), 1, 0);

	for (int k = 0; k < numPlayers_; k++) {
		Entity* newRocket = entityManager_->addEntity();
		//We could move the rockets using only the Viewer, but this will make
		//the logic much much easier.

		AnimatedViewer* viewer = newRocket->addComponent<AnimatedViewer>(Resources::RocketSpriteSheet, rocketRect, 10, b2Vec2(startingXPosition_ + k * distanceGainedByPoint_, initPos + (distanceBetweenRockets_ * k) + rocketRect.h / 2), -1, 0);
		playerRockets_.push_back(viewer);
	}
}

void MidGameState::render()
{
	fondo->render(0, 0);
	GameState::render();
}

void MidGameState::update()
{
	GameState::update();
	currentFrame++;

	if (currentFrame >= framesUntilNextShake_) {
		if (currentState != zoom) {

			int randDirX = 1, randDirY = 1;
			if (rand() % 2 == 0) randDirX = -1;
			if (rand() % 2 == 0) randDirY = -1;

			playerRockets_[roundWinner_]->setOffset(b2Vec2(rand() % shakeOffsetDistance_ * randDirX, rand() % shakeOffsetDistance_ * randDirY));
		}

		else {
			for (int k = 0; k < playerRockets_.size(); k++) {
				int randDirX = 1, randDirY = 1;
				if (rand() % 2 == 0) randDirX = -1;
				if (rand() % 2 == 0) randDirY = -1;

				playerRockets_[k]->setOffset(b2Vec2(rand() % shakeOffsetDistance_ * randDirX, rand() % shakeOffsetDistance_ * randDirY));
			}
		}

		framesUntilNextShake_ = currentFrame + framesBetweenShakes_;
	}

	if (currentState == waiting) {
		if (currentFrame == watingStateDuration_) {
			currentState = movingWinner;
			rocketXPositionObjective_ = playerRockets_[roundWinner_]->getPosUIElement().x + distanceGainedByPoint_;
		}
	}

	else if (currentState == movingWinner) {
		playerRockets_[roundWinner_]->setPosUIElement(b2Vec2(playerRockets_[roundWinner_]->getPosUIElement().x + distanceGainedPerFrame_, playerRockets_[roundWinner_]->getPosUIElement().y));

		if (playerRockets_[roundWinner_]->getPosUIElement().x > rocketXPositionObjective_) {
			currentState = zoom;
			frameZoomStateEnds_ = currentFrame + zoomStateDuration_;
		}
	}
	else if (currentState == zoom) {
		spaceStationScaleFactor_ += scaleGrowthPerFrame_;
		spaceStationViewer_->setScale(spaceStationScaleFactor_);

		for (int k = 0; k < playerRockets_.size(); k++) {
			int dirY = 1;
			if (k < playerRockets_.size() / 2) dirY = -1;
			playerRockets_[k]->setPosUIElement(b2Vec2(playerRockets_[k]->getPosUIElement().x + rocketMovementX_, playerRockets_[k]->getPosUIElement().y + rocketMovementY_ * dirY));
		}
		if (currentFrame >= frameZoomStateEnds_) {
			SDL_Game::instance()->getStateMachine()->transitionToState(States::play, 4, 1, "BoilerRoom");

		}
	}
	//Como no escalar las cosas
	/*else if (spaceStationAnimationStarted_ && spaceStationScaleFactor_ <= maxScaleSpaceStation_) {


		//// calculate new x and y
		//double new_x = (spaceStationViewer_->getPosUIElement().x - (300 * spaceStationScaleFactor_ - (300 * spaceStationScaleFactor_ - 0.5)) / 2);
		//double new_y = (spaceStationViewer_->getPosUIElement().y - (150 * spaceStationScaleFactor_ - (150 * spaceStationScaleFactor_ - 0.5)) / 2);

		//spaceStationViewer_->setOffset(b2Vec2(300 / 2, 150 / 2));

		//spaceStationViewer_->setPosUIElement(b2Vec2(new_x, new_y));

		//NO SABEMOS HACER MATES.

	}*/

}

void MidGameState::handleInput()
{
	GameState::handleInput();

}

void MidGameState::resetScene() {
	currentState = waiting;
	currentFrame = 0;
	spaceStationScaleFactor_ = 1;
	framesUntilNextShake_ = 0;
	spaceStationViewer_->setScale(spaceStationScaleFactor_);

	int initPos = (CONST(int, "WINDOW_HEIGHT") / 2) - (-distanceBetweenRockets_ / 2 + (distanceBetweenRockets_ / 2 * numPlayers_));

	SDL_Rect rocketRect;
	rocketRect.x = rocketRect.y = 0;
	rocketRect.w = 160;
	rocketRect.h = 76;

	for (int k = 0; k < playerRockets_.size(); k++) {
		playerRockets_[k]->setPosUIElement(b2Vec2(startingXPosition_ + k * distanceGainedByPoint_, initPos + (distanceBetweenRockets_ * k) + rocketRect.h / 2));
	}
}