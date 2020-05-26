#include "OnlineMenuState.h"
#include "InputHandler.h"
#include "SDL_Game.h"
#include "GameStateMachine.h"
#include "Texture.h"
#include "UIViewer.h"
#include "Constants.h"
#include "checkML.h"
#include "InputBinder.h"
#include "MatchInfo.h"

void OnlineMenuState::init() {
	entityManager_ = new EntityManager();
	ownerPlayerBinder_ = SDL_Game::instance()->getStateMachine()->getMatchInfo()->getPlayersInfo()->at(ownerPlayerID_)->inputBinder;
	Entity* miniTinky = entityManager_->addEntity();
	menuCursor_ = miniTinky->addComponent<UIViewer>(Resources::Rocket, b2Vec2(0, 0), 1, 90);
	menuCursor2_ = miniTinky->addComponent<UIViewer>(Resources::Rocket, b2Vec2(0, 0), 1, 270);
	cursorTexture_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Rocket);

	createText();
	updatePointer(0);

	//FONDO
	fondo_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::SpaceBackground);
}

void OnlineMenuState::handleInput()
{
	GameState::handleInput();
	//mover arriba y abajo
	if (!holdingY_)
	{
		if (ownerPlayerBinder_->menuMove(Dir::Down)) {
			updatePointer(1);
			holdingY_ = true;
		}
		else if (ownerPlayerBinder_->menuMove(Dir::Up)) {
			updatePointer(-1);
			holdingY_ = true;
		}
	}
	else if (!ownerPlayerBinder_->menuMove(Dir::Up) && !ownerPlayerBinder_->menuMove(Dir::Down)) {
		holdingY_ = false;
	}

	if (ownerPlayerBinder_->menuForward()) {
		switch (pointer_) {
		case 0: //local
			SDL_Game::instance()->getStateMachine()->changeToState(States::menu);
			break;
		case 1: //host
			SDL_Game::instance()->getHost();
			SDL_Game::instance()->getStateMachine()->changeToState(States::menu);
			break;
		case 2: //join
			SDL_Game::instance()->getStateMachine()->changeToState(States::client);
			break;
		case 3: //tutorial
			roundsVector_ = new vector<pair<GamemodeID, string>>();
			roundsVector_->push_back(std::make_pair(GamemodeID::Tutorial, "TutorialRoom"));
			SDL_Game::instance()->getStateMachine()->getMatchInfo()->setRounds(roundsVector_);
			SDL_Game::instance()->getStateMachine()->transitionToState(States::play, roundsVector_->front().first, roundsVector_->front().second);
		}
	}
}

void OnlineMenuState::onLoaded() { //poner el menu al principio
	//SDL_Game::instance()->getAudioMngr()->playMusic(Resources::AudioId::MainMenuMusic, -1);
	pointer_ = 0;
}

void OnlineMenuState::updatePointer(int n) {
	int size = Resources::Tutorial - Resources::Local + 1;

	//moverse en el menu de manera modular
	pointer_ += size + n;
	pointer_ %= size;

	menuCursor_->setPosUIElement(b2Vec2(xOffset_ - textures_[pointer_]->getWidth() * 1.5 / 2 - cursorTexture_->getWidth() * 2, yOffset_ * (pointer_ + 1) - 50));
	menuCursor2_->setPosUIElement(b2Vec2(xOffset_ + textures_[pointer_]->getWidth() * 1.5 / 2 + cursorTexture_->getWidth(), yOffset_ * (pointer_ + 1) - 50));
}

void OnlineMenuState::createText() { //preparar los textos
	int start, end, offset;

	start = Resources::Local;
	end = Resources::Tutorial;

	offset = start - 1;

	while (start <= end) {
		texts_.push_back(entityManager_->addEntity());
		textures_.push_back(SDL_Game::instance()->getTexturesMngr()->getTexture(start));
		texts_.back()->addComponent<UIViewer>(start, b2Vec2(xOffset_ - textures_.back()->getWidth() * 1.5 / 2, (start - offset) * yOffset_), 1.5, 0);
		start++;
	}
}

void OnlineMenuState::render() {
	fondo_->render(0, 0);
	GameState::render();
}