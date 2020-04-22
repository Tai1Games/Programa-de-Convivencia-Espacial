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

	pauseText->addComponent<Viewer>(Resources::PauseText, b2Vec2((CONST(int,"WINDOW_WIDTH") / 2) - 230, (CONST(int,"WINDOW_HEIGHT") / 2) - 310), 2.5, 0);
	
	btns_.push_back(resumeText->addComponent<Viewer>(Resources::ResumeText, b2Vec2((CONST(int, "WINDOW_WIDTH") / 2) - 260, (CONST(int, "WINDOW_HEIGHT") / 2) - 120), 1.5, 0));
	btns_.push_back(soundText->addComponent<Viewer>(Resources::SoundText, b2Vec2((CONST(int, "WINDOW_WIDTH") / 2) - 260, (CONST(int, "WINDOW_HEIGHT") / 2)), 1.5, 0));
	btns_.push_back(exitText->addComponent<Viewer>(Resources::ExitText, b2Vec2((CONST(int, "WINDOW_WIDTH") / 2) - 260, (CONST(int, "WINDOW_HEIGHT") / 2) + 120), 1.5, 0));

	buttonSelectorImage_ = miniTinky->addComponent<Viewer>(Resources::Tinky, b2Vec2(btns_[selectedBtn_]->getPosUIElement().x - 80, btns_[selectedBtn_]->getPosUIElement().y - 15), 0.5, 0);
	sliderControlImage_ = sliderControl->addComponent<Viewer>(Resources::SliderControl, b2Vec2(btns_[Buttons::Sound]->getPosUIElement().x + 645, btns_[Buttons::Sound]->getPosUIElement().y), 2, 0);
	slider->addComponent<Viewer>(Resources::Slider, b2Vec2(btns_[Buttons::Sound]->getPosUIElement().x + 360, btns_[Buttons::Sound]->getPosUIElement().y), 2,0);
}

void PauseState::handleInput()
{
	GameState::handleInput();
	InputHandler* ih = SDL_Game::instance()->getInputHandler();
	double lStickXValue;
	double lStickYValue;

	//Input específico para el botón seleccionado
	switch (selectedBtn_)
	{
	case Buttons::Resume:
		if (ih->isButtonJustUp(ownerPlayerID_, SDL_CONTROLLER_BUTTON_A))
		SDL_Game::instance()->getStateMachine()->changeToState(States::play);
		break;
	case Buttons::Sound:
		lStickXValue = ih->getStickX(ownerPlayerID_, InputHandler::GAMEPADSTICK::LEFTSTICK);
		if (currentMusicVolume_> 0 && !holdingX_ && lStickXValue < -0.999) {
			currentMusicVolume_ -= 10;
			updateMusicVolume();
			holdingX_ = true;
		}
		else if (currentMusicVolume_ < CONST(int,"MAX_MUSIC_VOLUME") && !holdingX_ && lStickXValue > 0.999) {
			currentMusicVolume_ += 10;
			updateMusicVolume();
			holdingX_ = true;
		}
		else if (holdingX_ && lStickXValue == 0) {
			holdingX_ = false;
		}
		break;
	case Buttons::Exit:
		/*Salir al menú cuando exista menú*/
		if (ih->isButtonJustUp(ownerPlayerID_, SDL_CONTROLLER_BUTTON_A))
		SDL_Game::instance()->getStateMachine()->changeToState(States::menu, ownerPlayerID_);
		break;
	}

	//Input general para el menú
	if (ih->isButtonJustUp(ownerPlayerID_, SDL_CONTROLLER_BUTTON_START) ||
		ih->isButtonJustUp(ownerPlayerID_, SDL_CONTROLLER_BUTTON_GUIDE)) {
		selectedBtn_ = 0;
		updateSelectedButton();
		SDL_Game::instance()->getStateMachine()->changeToState(States::play);
	}

	lStickYValue = ih->getStickY(ownerPlayerID_, InputHandler::GAMEPADSTICK::LEFTSTICK);

	if (!holdingY_ && lStickYValue > 0.9) {
		selectedBtn_++;
		updateSelectedButton();
		holdingY_ = true;
	}
	else if (!holdingY_ && lStickYValue < -0.9) {
		selectedBtn_--;
		updateSelectedButton();
		holdingY_ = true;
	}
	else if (holdingY_ && lStickYValue > -0.2 && lStickYValue < 0.2) {
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

	float newXPos = (btns_[Buttons::Sound]->getPosUIElement().x + 395) + ((currentMusicVolume_ / 10) * (250 / (CONST(double, "MAX_MUSIC_VOLUME")/ 10)));
	sliderControlImage_->setPosUIElement(b2Vec2(newXPos,
		btns_[Buttons::Sound]->getPosUIElement().y));
}
