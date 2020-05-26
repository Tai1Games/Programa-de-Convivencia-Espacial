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
	menuCursor_ = miniTinky->addComponent<UIViewer>(Resources::Tinky, b2Vec2(0, 0), 0.5, 0);
	menuCursor_->setPosUIElement(b2Vec2(tinkyOffset_, yOffset_ * (pointer_ + 1)));
	createText();

	//MUSICA
	//SDL_Game::instance()->getAudioMngr()->playMusic(Resources::AudioId::MainMenuMusic, -1);
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
		}
	}
}

void OnlineMenuState::onLoaded() { //poner el menu al principio
	//SDL_Game::instance()->getAudioMngr()->playMusic(Resources::AudioId::MainMenuMusic, -1);
	pointer_ = 0;
}

void OnlineMenuState::updatePointer(int n) {
	int size = 3;

	//moverse en el menu de manera modular
	pointer_ += size + n;
	pointer_ %= size;

	menuCursor_->setPosUIElement(b2Vec2(tinkyOffset_, yOffset_ * (pointer_ + 1)));
}

void OnlineMenuState::createText() { //preparar los textos
	int start, end, offset;

	start = Resources::Local;
	end = Resources::Join;

	offset = start - 1;

	while (start <= end) {
		texts_.push_back(entityManager_->addEntity());
		texts_.back()->addComponent<UIViewer>(start, b2Vec2(xOffset_, (start - offset) * yOffset_), 1.5, 0);
		start++;
	}
}
