#include "MenuState.h"
#include "InputHandler.h"
#include "SDL_Game.h"
#include "GameStateMachine.h"
#include "Texture.h"
#include "Viewer.h"
#include "Constants.h"

void MenuState::init() {
	entityManager_ = new EntityManager();

	Entity* miniTinky = entityManager_->addEntity();
	menuCursor_ = miniTinky->addComponent<Viewer>(Resources::Tinky, b2Vec2(tinkyOffset_, 2*yOffset_), 0.5, 0);
	updateText();
}

void MenuState::handleInput()
{
	GameState::handleInput();
	InputHandler* ih = SDL_Game::instance()->getInputHandler();
	double lStickYValue = ih->getStickY(ownerPlayerID_, InputHandler::GAMEPADSTICK::LEFTSTICK);	

	if (!holdingY_ && lStickYValue > 0.9) {
		updatePointer(1);
		holdingY_ = true;
	}
	else if (!holdingY_ && lStickYValue < -0.9) {
		updatePointer(-1);
		holdingY_ = true;
	}
	else if (holdingY_ && lStickYValue > -0.2 && lStickYValue < 0.2) {
		holdingY_ = false;
	}

	if (ih->isButtonJustUp(ownerPlayerID_, SDL_CONTROLLER_BUTTON_A)) {
		if (menuPointer_ < 2) {
			if (modePointer_ != 5) {
				menuPointer_++;
				updateText();
			}
			else SDL_Game::instance()->exitGame();
		}
		else {
			SDL_Game::instance()->getStateMachine()->changeToState(States::play, playerPointer_ + 1, modePointer_, maps_[mapPointer_]);
			SDL_Game::instance()->getStateMachine()->deleteState(States::menu); //se borra a sí mismo para poder volver a crearse
		}
	}
}

void MenuState::updatePointer(int n) {
	switch (menuPointer_) {
	case 0:
		if (n == 1) modePointer_++;
		else modePointer_ += GamemodeID::NUMBER_OF_GAMEMODES;
		modePointer_ %= (GamemodeID::NUMBER_OF_GAMEMODES + 1);	
		menuCursor_->setPosUIElement(b2Vec2(tinkyOffset_, yOffset_ * (modePointer_ + 2)));
		break;
	case 1:
		if (n == 1) mapPointer_++;
		else mapPointer_ += maps_.size()-1;
		mapPointer_ %= maps_.size();
		menuCursor_->setPosUIElement(b2Vec2(tinkyOffset_, yOffset_ * (mapPointer_ + 2)));
		break;
	case 2:
		if (n == 1) playerPointer_++;
		else playerPointer_ += 3;
		playerPointer_ %= 4;
		menuCursor_->setPosUIElement(b2Vec2(tinkyOffset_, yOffset_ * (playerPointer_ + 2)));
		break;
	}
}

void MenuState::updateText() {
	menuCursor_->setPosUIElement(b2Vec2(tinkyOffset_, 2*yOffset_));
	int end = Resources::LivingRoomText;

	if (menuPointer_ == 1) end = Resources::One;
	else if (menuPointer_ == 2) end = Resources::Five;

	for (Entity* e : texts_) e->setActive(false);

	while (i < end) {
		texts_.push_back(entityManager_->addEntity());
		texts_.back()->addComponent<Viewer>(i, b2Vec2(xOffset_, (i -j) * yOffset_), 1.5, 0); 
		i++;
	}

	j = i-2;
}
