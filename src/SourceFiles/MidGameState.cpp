#include "MidGameState.h"
#include "Collider.h"
#include "Resources.h"
#include "AnimatedViewer.h"
#include "AnimatedUIViewer.h"
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

	distanceGainedByPoint_ = (CONST(int, "WINDOW_WIDTH")- CONST(int, "START_POSITION")) / totalRounds;

	//Marcadores de las rondas
	for (int i = 0; i < totalRounds; i++) {
		Entity* marker = entityManager_->addEntity();
		marker->addComponent<UIViewer>(Resources::Token, b2Vec2((CONST(int, "START_POSITION")+ distanceGainedByPoint_*i)- CONST(int, "MARKER_WIDTH"), CONST(int, "MARKER_Y_POSITION")), 2, 0);
		markers.push_back(marker);
	}

	
	
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
	spaceStationViewer_ = spaceStation->addComponent<AnimatedUIViewer>(Resources::SpaceStation, stationRect, 3, b2Vec2(CONST(int, "WINDOW_WIDTH") / 2 - CONST(int, "SPACE_STATION_WIDTH") / 2, CONST(int, "WINDOW_HEIGHT") / 2 - CONST(int, "SPACE_STATION_HEIGHT") / 2), 1, 0);

	for (int k = 0; k < numPlayers_; k++) {
		Entity* newRocket = entityManager_->addEntity();
		//We could move the rockets using only the Viewer, but this will make
		//the logic much much easier.

		AnimatedUIViewer* viewer = newRocket->addComponent<AnimatedUIViewer>(Resources::RocketSpriteSheet, rocketRect, 10, b2Vec2(CONST(int, "START_POSITION"), initPos + (distanceBetweenRockets_ * k) + rocketRect.h / 2), -1, 0);
		playerRockets_.push_back(viewer);
	}
	//Texto para terminar la intermision
	continueText = entityManager_->addEntity();
	continueText->addComponent<UIViewer>(Resources::ContinueText, b2Vec2((CONST(int, "WINDOW_WIDTH") / 2) - 600, CONST(int, "WINDOW_HEIGHT") - 130), 1, 0);
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

		framesUntilNextShake_ = currentFrame + CONST(int, "FRAMES_PER_SHAKE");
	}

	switch (currentState) {
		case animationState::waiting:
			if (currentFrame >= CONST(int, "WAITING_DURATION")) {
				currentState = movingWinner;
				rocketXPositionObjective_ = playerRockets_[roundWinner_]->getPosUIElement().x + distanceGainedByPoint_;
			}
		break;

		case animationState::movingWinner:
			playerRockets_[roundWinner_]->setPosUIElement(b2Vec2(playerRockets_[roundWinner_]->getPosUIElement().x + CONST(int, "ROCKET_VEL"), playerRockets_[roundWinner_]->getPosUIElement().y));

			if (playerRockets_[roundWinner_]->getPosUIElement().x > rocketXPositionObjective_) {
				currentState = waitingButton;
				continueText->setActive(true);
				//frameZoomStateEnds_ = currentFrame + zoomStateDuration_;
			}
		break;

		case animationState::waitingButton:
			if (buttonPush) {
				currentState = zoom;
				frameZoomStateEnds_ = currentFrame + CONST(int, "ZOOM_DURATION");

				for (int i = 0; i < markers.size(); i++) {
					markers[i]->setActive(false);
				}
			}
		break;

		case animationState::zoom:
			for (int k = 0; k < playerRockets_.size(); k++) {
				int dirY = 1;
				if (k < playerRockets_.size() / 2) dirY = -1;
				playerRockets_[k]->setPosUIElement(b2Vec2(playerRockets_[k]->getPosUIElement().x + CONST(int, "ROCKET_SHAKE_X"), playerRockets_[k]->getPosUIElement().y + CONST(int, "ROCKET_SHAKE_Y") * dirY));
			}
			if (currentFrame >= frameZoomStateEnds_) {
				//Aqui pedirá a la super clase que ya se ponga el nuevo mapa y esas cosas
				SDL_Game::instance()->getAudioMngr()->resumeMusic();
				SDL_Game::instance()->getStateMachine()->transitionToState(States::play);

			}

			//Altamente provisional hasta que sepamos hacer mates
			spaceStationScaleFactor_ += CONST(double, "SCALE_GROWTH");
			spaceStationViewer_->setScale(spaceStationScaleFactor_);

			//Numeros mágicos yeiiii
			double new_x = (spaceStationViewer_->getPosUIElement().x - 3.0);
			double new_y = (spaceStationViewer_->getPosUIElement().y - 1.25);

			spaceStationViewer_->setScale(spaceStationScaleFactor_);
			spaceStationViewer_->setPosUIElement(b2Vec2(new_x, new_y));
			//NO SABEMOS HACER MATES.
		break;
	}
	
}

void MidGameState::handleInput()
{
	GameState::handleInput();
	InputHandler* ih = SDL_Game::instance()->getInputHandler();
	
	//Has esperado para ver hasta donde se movia el cohete
	if (currentState == waitingButton && (ih->keyDownEvent() || ih->isButonDownEvent())) {
		buttonPush = true;
		continueText->setActive(false);
	}
	//Eres un prisa y solo quieres matar
	else if (currentState != waitingButton && (ih->keyDownEvent() || ih->isButonDownEvent())) {
		currentState = zoom;
		frameZoomStateEnds_ = currentFrame + CONST(int, "ZOOM_DURATION");
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

	roundWinner_ = 0;	//Nos lo dará la clase superior

	int initPos = (CONST(int, "WINDOW_HEIGHT") / 2) - (-distanceBetweenRockets_ / 2 + (distanceBetweenRockets_ / 2 * numPlayers_));

	SDL_Rect rocketRect;
	rocketRect.x = rocketRect.y = 0;
	rocketRect.w = 160;
	rocketRect.h = 76;

	spaceStationViewer_->setPosUIElement(b2Vec2(CONST(int, "WINDOW_WIDTH") / 2 - CONST(int, "SPACE_STATION_WIDTH") / 2, CONST(int, "WINDOW_HEIGHT") / 2 - CONST(int, "SPACE_STATION_HEIGHT") / 2));

	int playerPoints[] = {4,2,1,3};		//Para probar pero lo dará la super clase

	for (int i = 0; i < markers.size(); i++) {
		markers[i]->setActive(true);
	}

	for (int k = 0; k < playerRockets_.size(); k++) {
		playerRockets_[k]->setPosUIElement(b2Vec2(CONST(int, "START_POSITION") + distanceGainedByPoint_ * playerPoints[k], initPos + (distanceBetweenRockets_ * k) + rocketRect.h / 2));
	}
}