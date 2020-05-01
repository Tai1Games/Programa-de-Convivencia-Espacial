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

	for (int k = 0; k < numPlayers_; k++) {
		Entity* newRocket = entityManager_->addEntity();
		//We could move the rockets using only the Viewer, but this will make
		//the logic much much easier.

		AnimatedViewer* viewer = newRocket->addComponent<AnimatedViewer>(Resources::RocketSpriteSheet, rocketRect, 10, b2Vec2(startingXPosition_ + k * distanceGainedByPoint_, initPos + (distanceBetweenRockets_ * k) - 0.5), -1, 0);
		playerRockets_.push_back(viewer);
	}

	SDL_Rect stationRect;
	stationRect.x = 0;
	stationRect.y = 0;
	stationRect.w = 300;
	stationRect.h = 150;

	Entity* spaceStation = entityManager_->addEntity();
	spaceStationViewer_ = spaceStation->addComponent<AnimatedViewer>(Resources::SpaceStation, stationRect, 3, b2Vec2(CONST(int, "WINDOW_WIDTH") / 2 - spaceStationWidht_ / 2, CONST(int, "WINDOW_HEIGHT") / 2 - spaceStationHeight_ / 2), 1, 0);
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
	if (currentFrame > framesUntilAnimationStart_ && !rocketAnimationStarted_) {
		rocketAnimationStarted_ = true;
		rocketXPositionObjective_ = playerRockets_[roundWinner_]->getPosUIElement().x + distanceGainedByPoint_;
	}
	else if (rocketAnimationStarted_ && !rocketAnimationEnded_) {
		playerRockets_[roundWinner_]->setPosUIElement(b2Vec2(playerRockets_[roundWinner_]->getPosUIElement().x + distanceGainedPerFrame_, playerRockets_[roundWinner_]->getPosUIElement().y));

		if (playerRockets_[roundWinner_]->getPosUIElement().x > rocketXPositionObjective_) rocketAnimationEnded_ = true;
	}

}

void MidGameState::handleInput()
{
	GameState::handleInput();
}