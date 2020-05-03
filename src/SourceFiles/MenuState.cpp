#include "MenuState.h"
#include "InputHandler.h"
#include "SDL_Game.h"
#include "GameStateMachine.h"
#include "Texture.h"
#include "Viewer.h"
#include "Constants.h"
#include "checkML.h"


void MenuState::init() {
	entityManager_ = new EntityManager();

	Entity* miniTinky = entityManager_->addEntity();
	menuCursor_ = miniTinky->addComponent<Viewer>(Resources::Tinky, b2Vec2(0, 0), 0.5, 0);
	createText();
	updateText(-1);

	//MÚSICA
	SDL_Game::instance()->getAudioMngr()->playMusic(Resources::AudioId::MainMenuMusic, -1);
}

void MenuState::handleInput()
{
	GameState::handleInput();
	InputHandler* ih = SDL_Game::instance()->getInputHandler();
	double lStickYValue = ih->getStickY(ownerPlayerID_, InputHandler::GAMEPADSTICK::LEFTSTICK);
	//mover arriba y abajo
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

	if (ih->isButtonJustDown(ownerPlayerID_, SDL_CONTROLLER_BUTTON_A)) {
		if (menuPointer_ < 2) {
			if (pointers_[0] < NUMBER_OF_GAMEMODES - 1) {
				menuPointer_++;
				updateText(menuPointer_ -1);
			}
			else if (pointers_[0] < NUMBER_OF_GAMEMODES) {
				menuPointer_ += 2;
				pointers_[1] = -1;
				updateText(menuPointer_ - 2);
			}
			else SDL_Game::instance()->exitGame();
		}
		else {
			if (pointers_[1] == -1) SDL_Game::instance()->getStateMachine()->transitionToState(States::play, pointers_[2] + 1, pointers_[0], "TutorialRoom");
			else SDL_Game::instance()->getStateMachine()->transitionToState(States::play, pointers_[2] + 1, pointers_[0], maps_[pointers_[1]]);
		}
	}
	//ir para atrás
	else if (ih->isButtonJustUp(ownerPlayerID_, SDL_CONTROLLER_BUTTON_B)) {
		if (menuPointer_ > 0) {
			if (pointers_[0] != NUMBER_OF_GAMEMODES - 1) {
				menuPointer_--;
				updateText(menuPointer_ + 1);
			}
			else {
				menuPointer_ -= 2;
				pointers_[1] = 0;
				updateText(menuPointer_ + 2);
			}			
		}
	}
}

void MenuState::onLoaded() {
	SDL_Game::instance()->getAudioMngr()->playMusic(Resources::AudioId::MainMenuMusic, -1);
	menuPointer_ = 0;
	updateText(2);
}

void MenuState::updatePointer(int n) {
	int size = 0;
	switch (menuPointer_) {
	case 0:
		size = GamemodeID::NUMBER_OF_GAMEMODES + 1;
		break;
	case 1:
		size = maps_.size();
		break;
	case 2:
		size = 4;
		break;
	}
	if (n == 1) pointers_[menuPointer_]++;
	else pointers_[menuPointer_] += size - 1;

	pointers_[menuPointer_] %= size;
	menuCursor_->setPosUIElement(b2Vec2(tinkyOffset_, yOffset_ * (pointers_[menuPointer_] + 1)));
}

void MenuState::updateText(int previous) {
	menuCursor_->setPosUIElement(b2Vec2(tinkyOffset_, yOffset_ * (pointers_[menuPointer_] + 1)));

	if (previous != -1) for (Entity* e : texts_[previous]) e->setActive(false);
	for (Entity* e : texts_[menuPointer_]) e->setActive(true);
}

void MenuState::createText() {
	int start, end, offset;

	for (int i = 0; i < 3; i++) {
		switch (i) {
		case 0:
			start = Resources::Capitalism;
			end = Resources::LivingRoomText;
			break;
		case 1:
			end = Resources::OnePlayer;
			break;
		case 2:
			end = Resources::FivePlayers;
			break;
		}

		offset = start - 1;

		while (start < end) {
			texts_[i].push_back(entityManager_->addEntity());
			texts_[i].back()->addComponent<Viewer>(start, b2Vec2(xOffset_, (start - offset) * yOffset_), 1.5, 0);
			texts_[i].back()->setActive(false);
			start++;
		}
	}
}
