#include "MidGameState.h"
#include "Collider.h"
#include "Resources.h"
#include "AnimatedViewer.h"
#include "Entity.h"
#include "SDL_Game.h"
#include "InputHandler.h"


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

		AnimatedViewer* viewer = newRocket->addComponent<AnimatedViewer>(Resources::RocketSpriteSheet, rocketRect, 10, b2Vec2(startingXPosition_ /*+ k * distanceGainedByPoint_*/, initPos + (distanceBetweenRockets_ * k) + rocketRect.h / 2), -1, 0);
		playerRockets_.push_back(viewer);
	}
	//Texto para terminar la intermision
	continueText = entityManager_->addEntity();
	continueText->addComponent<Viewer>(Resources::ContinueText, b2Vec2((CONST(int, "WINDOW_WIDTH") / 2) - 400, (CONST(int, "WINDOW_HEIGHT") / 2) + 180), 1, 0);
	continueText->setActive(false);
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
			currentState = waitingButton;
			continueText->setActive(true);
			//frameZoomStateEnds_ = currentFrame + zoomStateDuration_;
		}
	}
	else if (currentState == waitingButton && buttonPush) {
		currentState = zoom;
		frameZoomStateEnds_ = currentFrame + zoomStateDuration_;
	}

	else if (currentState == zoom) {

		for (int k = 0; k < playerRockets_.size(); k++) {
			int dirY = 1;
			if (k < playerRockets_.size() / 2) dirY = -1;
			playerRockets_[k]->setPosUIElement(b2Vec2(playerRockets_[k]->getPosUIElement().x + rocketMovementX_, playerRockets_[k]->getPosUIElement().y + rocketMovementY_ * dirY));
		}
		if (currentFrame >= frameZoomStateEnds_) {
			//Aqui pedir� a la super clase que ya se ponga el nuevo mapa y esas cosas
			SDL_Game::instance()->getStateMachine()->transitionToState(States::play, 4, 1, "BoilerRoom");

		} 

		//Altamente provisional hasta que sepamos hacer mates
		spaceStationScaleFactor_ += scaleGrowthPerFrame_;
		spaceStationViewer_->setScale(spaceStationScaleFactor_);

		//Numeros m�gicos yeiiii
		double new_x = (spaceStationViewer_->getPosUIElement().x - 3.0);
		double new_y = (spaceStationViewer_->getPosUIElement().y - 1.25);

		spaceStationViewer_->setScale(spaceStationScaleFactor_);
		spaceStationViewer_->setPosUIElement(b2Vec2(new_x, new_y));
		//NO SABEMOS HACER MATES.
	}
	
}

void MidGameState::handleInput()
{
	GameState::handleInput();
	InputHandler* ih = SDL_Game::instance()->getInputHandler();
	for (size_t i = 0; i < ih->getNumControllers(); i++)
	{
		//Has esperado para ver hasta donde se movia el cohete
		if (currentState == waitingButton && ih->isButtonJustDown(i, SDL_CONTROLLER_BUTTON_A)) {
			buttonPush = true;
			continueText->setActive(false);
		}
		//Eres un prisa y solo quieres matar
		else if (currentState != waitingButton && ih->isButtonJustDown(i, SDL_CONTROLLER_BUTTON_A)) {
			currentState = zoom;
			frameZoomStateEnds_ = currentFrame + zoomStateDuration_;
		}
	}
	
}

void MidGameState::resetScene() {
	//Reseteamos el estado a como estaba en origen
	currentState = waiting;
	currentFrame = 0;
	spaceStationScaleFactor_ = 1;
	framesUntilNextShake_ = 0;
	spaceStationViewer_->setScale(spaceStationScaleFactor_);
	buttonPush = false;

	int initPos = (CONST(int, "WINDOW_HEIGHT") / 2) - (-distanceBetweenRockets_ / 2 + (distanceBetweenRockets_ / 2 * numPlayers_));

	SDL_Rect rocketRect;
	rocketRect.x = rocketRect.y = 0;
	rocketRect.w = 160;
	rocketRect.h = 76;

	spaceStationViewer_->setPosUIElement(b2Vec2(CONST(int, "WINDOW_WIDTH") / 2 - spaceStationWidht_ / 2, CONST(int, "WINDOW_HEIGHT") / 2 - spaceStationHeight_ / 2));

	int playerPoints[] = {4,2,1,3};		//Para probar pero lo dar� la super clase

	for (int k = 0; k < playerRockets_.size(); k++) {
		playerRockets_[k]->setPosUIElement(b2Vec2(startingXPosition_ + distanceGainedByPoint_ * playerPoints[k], initPos + (distanceBetweenRockets_ * k) + rocketRect.h / 2));
	}
}