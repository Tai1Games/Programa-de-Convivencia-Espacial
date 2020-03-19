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
	Entity* slider = entityManager_->addEntity();

	Entity* miniTinky = entityManager_->addEntity();
	Entity* sliderControl = entityManager_->addEntity();

	pauseText->addComponent<Viewer>(Resources::Pause, (WINDOW_WIDTH / 2) - 185, (WINDOW_HEIGHT / 2) - 310, 2);
	
	btns_.push_back(resumeText->addComponent<Viewer>(Resources::Resume, (WINDOW_WIDTH / 2) - 180, (WINDOW_HEIGHT / 2) - 100, 1));
	btns_.push_back(soundText->addComponent<Viewer>(Resources::Sound, (WINDOW_WIDTH / 2) - 180, (WINDOW_HEIGHT / 2), 1));
	btns_.push_back(exitText->addComponent<Viewer>(Resources::Exit, (WINDOW_WIDTH / 2) - 180, (WINDOW_HEIGHT / 2) + 100, 1));

	onBtnImage_ = miniTinky->addComponent<Viewer>(Resources::Tinky, (WINDOW_WIDTH / 2) - 250, btns_[Buttons::Resume]->getPosUIElement().y - 15, 0.4);
	sliderControlImage_ = sliderControl->addComponent<Viewer>(Resources::SliderControl, btns_[Buttons::Sound]->getPosUIElement().x + 550, btns_[Buttons::Sound]->getPosUIElement().y - 15, 2);
	slider->addComponent<Viewer>(Resources::Slider, btns_[Buttons::Sound]->getPosUIElement().x + 270, btns_[Buttons::Sound]->getPosUIElement().y - 15, 2);
}

void PauseState::handleInput()
{
	GameState::handleInput();
	InputHandler* ih = SDL_Game::instance()->getInputHandler();
	double rStickXValue;

	switch (selectedBtn_)
	{
	case Buttons::Resume:
		if (ih->isButtonJustDown(ownerPlayerID_, SDL_CONTROLLER_BUTTON_A))
		SDL_Game::instance()->getStateMachine()->changeToState(States::play);
		break;
	case Buttons::Sound:
		rStickXValue = ih->getStickX(ownerPlayerID_, InputHandler::GAMEPADSTICK::RIGHTSTICK);
		break;
	case Buttons::Exit:
		/*Salir al menú cuando exista menú*/
		/*SDL_Game::instance()->getStateMachine()->changeToState(States::menu);*/
		break;
	}

	double rStickYValue = ih->getStickY(ownerPlayerID_, InputHandler::GAMEPADSTICK::RIGHTSTICK);

	if (!holding_ && rStickYValue > 0.999) {
		selectedBtn_++;

		updateSelection();
	
	}
	else if (!holding_ && rStickYValue < -0.999) {
		selectedBtn_--;

		updateSelection();
	}
	else if (holding_ && rStickYValue == 0) {
		holding_ = false;
	}
	
}

void PauseState::updateSelection()
{
	if (selectedBtn_ >= 0) selectedBtn_ %= int(btns_.size());
	else {
		selectedBtn_ %= int(btns_.size());
		selectedBtn_ += int(btns_.size());
	}

	float newYPos = btns_[selectedBtn_]->getPosUIElement().y - 15;
	onBtnImage_->setPosUIElement(b2Vec2(onBtnImage_->getPosUIElement().x, newYPos));

	holding_ = true;
}
