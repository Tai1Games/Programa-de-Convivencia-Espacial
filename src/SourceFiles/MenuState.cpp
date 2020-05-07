#include "MenuState.h"
#include "InputHandler.h"
#include "SDL_Game.h"
#include "GameStateMachine.h"
#include "Texture.h"
#include "Viewer.h"
#include "Constants.h"
#include "checkML.h"
#include "InputBinder.h"
#include "MatchInfo.h"

void MenuState::init() {
	entityManager_ = new EntityManager();
	ownerPlayerBinder_ = SDL_Game::instance()->getStateMachine()->getMatchInfo()->getPlayersInfo()->at(ownerPlayerID_)->inputBinder;
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
		if (menuPointer_ == 0) { //Seleccionando gamemode
			if (pointers_[0] < GamemodeID::NUMBER_OF_GAMEMODES - 1) {
				menuPointer_++;
				pointers_[1] = 0;
				updateText(menuPointer_ -1);
			}
			else if (pointers_[0] == GamemodeID::Tutorial) { //Si es tutorial te manda directo sin seleccionar mapa
				pointers_[1] = -1;
				SDL_Game::instance()->getStateMachine()->transitionToState(States::play, pointers_[0], "TutorialRoom");
			}
			else SDL_Game::instance()->exitGame();
		}
		else { //Elegimos el mapa
			SDL_Game::instance()->getStateMachine()->transitionToState(States::play, pointers_[0], maps_[pointers_[1]]);
		}
	}
	//ir para atrás
	else if (ownerPlayerBinder_->menuBack() && (menuPointer_ > 0))
	{
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

void MenuState::onLoaded() {
	SDL_Game::instance()->getAudioMngr()->playMusic(Resources::AudioId::MainMenuMusic, -1);
	menuPointer_ = 0;
	pointers_[0] = 0;
	pointers_[1] = 0;
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
	default:
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

	for (int i = 0; i < 2; i++) {
		switch (i) {
		case 0:
			start = Resources::Capitalism;
			end = Resources::LivingRoomText;
			break;
		case 1:
			end = Resources::OnePlayer;
			break;
		default:
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
