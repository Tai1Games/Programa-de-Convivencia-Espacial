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

	pauseText->addComponent<Viewer>(Resources::PauseText, (WINDOW_WIDTH / 2) - 230, (WINDOW_HEIGHT / 2) - 310, 2.5);
	
	btns_.push_back(resumeText->addComponent<Viewer>(Resources::ResumeText, (WINDOW_WIDTH / 2) - 260, (WINDOW_HEIGHT / 2) - 120, 1.5));
	btns_.push_back(soundText->addComponent<Viewer>(Resources::SoundText, (WINDOW_WIDTH / 2) - 260, (WINDOW_HEIGHT / 2), 1.5));
	btns_.push_back(exitText->addComponent<Viewer>(Resources::ExitText, (WINDOW_WIDTH / 2) - 260, (WINDOW_HEIGHT / 2) + 120, 1.5));

	buttonSelectorImage_ = miniTinky->addComponent<Viewer>(Resources::Tinky, btns_[selectedBtn_]->getPosUIElement().x - 80, btns_[selectedBtn_]->getPosUIElement().y - 15, 0.5);
	sliderControlImage_ = sliderControl->addComponent<Viewer>(Resources::SliderControl, btns_[Buttons::Sound]->getPosUIElement().x + 645, btns_[Buttons::Sound]->getPosUIElement().y, 2);
	slider->addComponent<Viewer>(Resources::Slider, btns_[Buttons::Sound]->getPosUIElement().x + 360, btns_[Buttons::Sound]->getPosUIElement().y, 2);
}

void PauseState::handleInput()
{
	GameState::handleInput();
	InputHandler* ih = SDL_Game::instance()->getInputHandler();
	double rStickXValue;
	double rStickYValue;

	//Input específico para el botón seleccionado
	switch (selectedBtn_)
	{
	case Buttons::Resume:
		if (ih->isButtonJustDown(ownerPlayerID_, SDL_CONTROLLER_BUTTON_A))
		SDL_Game::instance()->getStateMachine()->changeToState(States::play);
		break;
	case Buttons::Sound:
		rStickXValue = ih->getStickX(ownerPlayerID_, InputHandler::GAMEPADSTICK::RIGHTSTICK);
		if (currentMusicVolume_> 0 && !holdingX_ && rStickXValue < -0.999) {
			currentMusicVolume_ -= 10;
			updateMusicVolume();
			holdingX_ = true;
		}
		else if (currentMusicVolume_ < MAX_MUSIC_VOLUME && !holdingX_ && rStickXValue > 0.999) {
			currentMusicVolume_ += 10;
			updateMusicVolume();
			holdingX_ = true;
		}
		else if (holdingX_ && rStickXValue == 0) {
			holdingX_ = false;
		}
		break;
	case Buttons::Exit:
		/*Salir al menú cuando exista menú*/
		/*if (ih->isButtonJustDown(ownerPlayerID_, SDL_CONTROLLER_BUTTON_A))*/
		/*SDL_Game::instance()->getStateMachine()->changeToState(States::menu);*/
		break;
	}

	//Input general para moverse por el menú
	rStickYValue = ih->getStickY(ownerPlayerID_, InputHandler::GAMEPADSTICK::RIGHTSTICK);

	if (!holdingY_ && rStickYValue > 0.999) {
		selectedBtn_++;
		updateSelectedButton();
		holdingY_ = true;
	}
	else if (!holdingY_ && rStickYValue < -0.999) {
		selectedBtn_--;
		updateSelectedButton();
		holdingY_ = true;
	}
	else if (holdingY_ && rStickYValue == 0) {
		holdingY_ = false;
	}
	
}

void PauseState::updateSelectedButton()
{
	if (selectedBtn_ >= 0) selectedBtn_ %= int(btns_.size());
	else {
		selectedBtn_ %= int(btns_.size());
		selectedBtn_ += int(btns_.size());
	}

	float newXPos = btns_[selectedBtn_]->getPosUIElement().x - 80;
	float newYPos = btns_[selectedBtn_]->getPosUIElement().y - 15;
	buttonSelectorImage_->setPosUIElement(b2Vec2(newXPos, newYPos));

}

void PauseState::updateMusicVolume()
{
	SDL_Game::instance()->getAudioMngr()->setMusicVolume(currentMusicVolume_);

	float newXPos = (btns_[Buttons::Sound]->getPosUIElement().x + 395) + ((currentMusicVolume_ / 10) * (250 / (MAX_MUSIC_VOLUME / 10)));
	sliderControlImage_->setPosUIElement(b2Vec2(newXPos,
		btns_[Buttons::Sound]->getPosUIElement().y));
}
