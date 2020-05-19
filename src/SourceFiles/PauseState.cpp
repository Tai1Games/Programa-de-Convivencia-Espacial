#include "PauseState.h"
#include "Texture.h"
#include "Resources.h"
#include "UIViewer.h"
#include "SDL_Game.h"
#include "InputBinder.h"
#include "GameStateMachine.h"
#include "MatchInfo.h"

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

	pauseText->addComponent<UIViewer>(Resources::PauseText, b2Vec2((CONST(int, "WINDOW_WIDTH") / 2) - 230, (CONST(int, "WINDOW_HEIGHT") / 2) - 310), 2.5, 0);

	btns_.push_back(resumeText->addComponent<UIViewer>(Resources::ResumeText, b2Vec2((CONST(int, "WINDOW_WIDTH") / 2) - 260, (CONST(int, "WINDOW_HEIGHT") / 2) - 120), 1.5, 0));
	btns_.push_back(soundText->addComponent<UIViewer>(Resources::SoundText, b2Vec2((CONST(int, "WINDOW_WIDTH") / 2) - 260, (CONST(int, "WINDOW_HEIGHT") / 2)), 1.5, 0));
	btns_.push_back(exitText->addComponent<UIViewer>(Resources::ExitText, b2Vec2((CONST(int, "WINDOW_WIDTH") / 2) - 260, (CONST(int, "WINDOW_HEIGHT") / 2) + 120), 1.5, 0));

	buttonSelectorImage_ = miniTinky->addComponent<UIViewer>(Resources::Tinky, b2Vec2(btns_[selectedBtn_]->getPosUIElement().x - 80, btns_[selectedBtn_]->getPosUIElement().y - 15), 0.5, 0);
	sliderControlImage_ = sliderControl->addComponent<UIViewer>(Resources::SliderControl, b2Vec2(btns_[Buttons::Sound]->getPosUIElement().x + 645, btns_[Buttons::Sound]->getPosUIElement().y), 2, 0);
	slider->addComponent<UIViewer>(Resources::Slider, b2Vec2(btns_[Buttons::Sound]->getPosUIElement().x + 360, btns_[Buttons::Sound]->getPosUIElement().y), 2, 0);

	cout << "Pause initialized to " << ownerPlayerID_ << endl;
	ownerBinder_ = SDL_Game::instance()->getStateMachine()->getMatchInfo()->getPlayersInfo()->at(ownerPlayerID_)->inputBinder;
}

void PauseState::handleInput()
{
	GameState::handleInput();

	//Input espec�fico para el bot�n seleccionado
	switch (selectedBtn_)
	{
	case Buttons::Resume:
		if (ownerBinder_->menuForward())
			resumeGame();
		break;
	case Buttons::Sound:
		if (!holdingX_)
		{
			if (currentMusicVolume_ > 0 && ownerBinder_->menuMove(Dir::Left)) {
				currentMusicVolume_ -= 10;
				updateMusicVolume();
				SDL_Game::instance()->getAudioMngr()->playChannel(Resources::MenuMove, 0);
				holdingX_ = true;
			}
			else if (currentMusicVolume_ < CONST(int, "MAX_MUSIC_VOLUME") && ownerBinder_->menuMove(Dir::Right)) {
				currentMusicVolume_ += 10;
				updateMusicVolume();
				SDL_Game::instance()->getAudioMngr()->playChannel(Resources::MenuMove, 0);
				holdingX_ = true;
			}
		}
		else if (holdingX_ && !ownerBinder_->menuMove(Dir::Right) && !ownerBinder_->menuMove(Dir::Left)) {
			holdingX_ = false;
		}
		break;
	case Buttons::Exit:
		if (ownerBinder_->menuForward()) {
			SDL_Game::instance()->getAudioMngr()->playChannel(Resources::MenuForward, 0);
			cout << "Pause ended for " << ownerPlayerID_ << endl;
			SDL_Game::instance()->getStateMachine()->changeToState(States::menu, ownerPlayerID_);
		}
		break;
	}

	//Input general para el men�
	if (ownerBinder_->pressPause()) {
		selectedBtn_ = 0;
		updateSelectedButton();
		resumeGame();
	}

	if (!holdingY_)
	{
		if (ownerBinder_->menuMove(Dir::Down)) {
			SDL_Game::instance()->getAudioMngr()->playChannel(Resources::MenuMove, 0);
			selectedBtn_++;
			updateSelectedButton();
			holdingY_ = true;
		}
		else if (ownerBinder_->menuMove(Dir::Up)) {
			SDL_Game::instance()->getAudioMngr()->playChannel(Resources::MenuMove, 0);
			selectedBtn_--;
			updateSelectedButton();
			holdingY_ = true;
		}
	}
	else if (holdingY_ && !ownerBinder_->menuMove(Dir::Up) && !ownerBinder_->menuMove(Dir::Down)) {
		holdingY_ = false;
	}
}

void PauseState::setOwner(int ownerID) {
	ownerPlayerID_ = ownerID;
	ownerBinder_ = SDL_Game::instance()->getStateMachine()->getMatchInfo()->getPlayersInfo()->at(ownerID)->inputBinder;
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

	float newXPos = (btns_[Buttons::Sound]->getPosUIElement().x + 395) + ((currentMusicVolume_ / 10) * (250 / (CONST(double, "MAX_MUSIC_VOLUME") / 10)));
	sliderControlImage_->setPosUIElement(b2Vec2(newXPos,
		btns_[Buttons::Sound]->getPosUIElement().y));
}

void PauseState::resumeGame()
{
	SDL_Game::instance()->getStateMachine()->changeToState(States::play);
	SDL_Game::instance()->getAudioMngr()->resumeMusic();
}