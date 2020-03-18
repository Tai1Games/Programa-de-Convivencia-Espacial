#include "PauseState.h"
#include "Texture.h"
#include "Resources.h"
#include "Viewer.h"
#include "SDL_Game.h"
#include "InputHandler.h"

void PauseState::init()
{
	entityManager_ = new EntityManager();

	Entity* pauseText = entityManager_->addEntity();
	Entity* resumeText = entityManager_->addEntity();
	Entity* soundText = entityManager_->addEntity();
	Entity* exitText = entityManager_->addEntity();

	Entity* miniTinky = entityManager_->addEntity();

	pauseText->addComponent<Viewer>(Resources::Pause, (WINDOW_WIDTH / 2) - 185, (WINDOW_HEIGHT / 2) - 310, 2);
	
	btns_.push_back(resumeText->addComponent<Viewer>(Resources::Resume, (WINDOW_WIDTH / 2) - 180, (WINDOW_HEIGHT / 2) - 100, 1));
	btns_.push_back(soundText->addComponent<Viewer>(Resources::Sound, (WINDOW_WIDTH / 2) - 180, (WINDOW_HEIGHT / 2), 1));
	btns_.push_back(exitText->addComponent<Viewer>(Resources::Exit, (WINDOW_WIDTH / 2) - 180, (WINDOW_HEIGHT / 2) + 100, 1));

	onBtnImage = miniTinky->addComponent<Viewer>(Resources::Tinky, (WINDOW_WIDTH / 2) - 250, btns_[selectedBtn_]->getPosUIElement().y - 15, 0.4);
}

void PauseState::handleInput()
{
	GameState::handleInput();
	InputHandler* ih = SDL_Game::instance()->getInputHandler();

	if (ih->isButtonJustUp(ownerPlayerID_, SDL_CONTROLLER_BUTTON_START) || 
		ih->isButtonJustUp(ownerPlayerID_, SDL_CONTROLLER_BUTTON_GUIDE)) {
		SDL_Game::instance()->getStateMachine()->changeToState(play);
	}
	else if (ih->isButtonJustDown(ownerPlayerID_, SDL_CONTROLLER_BUTTON_A)) {
			
	}
	else {
		double rStickValue = ih->getStickY(ownerPlayerID_, InputHandler::GAMEPADSTICK::RIGHTSTICK);
		
		if (!holding_ && rStickValue > 0.999) {
			selectedBtn_++;

			if(selectedBtn_>=0) selectedBtn_ %= int(btns_.size());
			else {
				selectedBtn_ %= int(btns_.size());
				selectedBtn_ += int(btns_.size());
			}

			float yPos = btns_[selectedBtn_]->getPosUIElement().y - 15;
			onBtnImage->setPosUIElement(b2Vec2(onBtnImage->getPosUIElement().x, yPos));
			holding_ = true;
	
		}
		else if (!holding_ && rStickValue < -0.999) {
			selectedBtn_--;

			if (selectedBtn_ >= 0) selectedBtn_ %= int(btns_.size());
			else{
				selectedBtn_ %= int(btns_.size());
				selectedBtn_ += int(btns_.size());
			}	

			float yPos = btns_[selectedBtn_]->getPosUIElement().y - 15;
			onBtnImage->setPosUIElement(b2Vec2(onBtnImage->getPosUIElement().x, yPos));
			holding_ = true;
		}
		else if (holding_ && rStickValue == 0) {
			holding_ = false;
		}
	}
	
}
