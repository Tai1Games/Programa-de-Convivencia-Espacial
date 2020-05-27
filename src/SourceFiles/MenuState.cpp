////////////////////////////////////////////////
/////////////// IN MEMORIAM ////////////////////
//Cuando todo era más simple y no había online//
///////////////////////////////////////////////


/*#include "MenuState.h"
#include "InputHandler.h"
#include "SDL_Game.h"
#include "GameStateMachine.h"
#include "Texture.h"
#include "UIViewer.h"
#include "Constants.h"
#include "checkML.h"
#include "InputBinder.h"
#include "MatchInfo.h"

void MenuState::init() {
	entityManager_ = new EntityManager();
	ownerPlayerBinder_ = SDL_Game::instance()->getStateMachine()->getMatchInfo()->getPlayersInfo()->at(ownerPlayerID_)->inputBinder;
	Entity* miniTinky = entityManager_->addEntity();
	menuCursor_ = miniTinky->addComponent<UIViewer>(Resources::Rocket, b2Vec2(0, 0), 0.8, 90);
	createText();
	updateText();

	//M�SICA
	SDL_Game::instance()->getAudioMngr()->playMusic(Resources::AudioId::MainMenuMusic, -1);
}

void MenuState::handleInput()
{
	GameState::handleInput();
	//mover arriba y abajo
	if (!holdingY_)
	{
		if (ownerPlayerBinder_->menuMove(Dir::Down)) {
			SDL_Game::instance()->getAudioMngr()->playChannel(Resources::MenuMove, 0);
			updatePointer(1);
			holdingY_ = true;
		}
		else if (ownerPlayerBinder_->menuMove(Dir::Up)) {
			SDL_Game::instance()->getAudioMngr()->playChannel(Resources::MenuMove, 0);
			updatePointer(-1);
			holdingY_ = true;
		}
	}
	else if (!ownerPlayerBinder_->menuMove(Dir::Up) && !ownerPlayerBinder_->menuMove(Dir::Down)) {
		holdingY_ = false;
	}

	if (ownerPlayerBinder_->menuForward()) {
		SDL_Game::instance()->getAudioMngr()->playChannel(Resources::MenuForward, 0);
		if (menuPointer_ == 0) { //Seleccionando gamemode
			if (pointers_[0] < GamemodeID::Tutorial) {
				menuPointer_++;
				updateText();
			}
			else if (pointers_[0] == GamemodeID::Tutorial) { //Si es tutorial te manda directo sin seleccionar mapa
				addRound((GamemodeID)pointers_[0], "TutorialRoom");
				SDL_Game::instance()->getStateMachine()->getMatchInfo()->setRounds(roundsVector_);
				SDL_Game::instance()->getStateMachine()->transitionToState(States::play, roundsVector_->front().first, roundsVector_->front().second);
			}
			else SDL_Game::instance()->exitGame();
		}
		else { //Elegimos el mapa
			addRound((GamemodeID)pointers_[0], maps_[pointers_[1]]);
			if (roundsVector_->size() == numberOfRounds_) {
				SDL_Game::instance()->getStateMachine()->getMatchInfo()->setRounds(roundsVector_);
				SDL_Game::instance()->getStateMachine()->transitionToState(States::play, roundsVector_->front().first, roundsVector_->front().second);
			}
			else { //como onLoaded pero sin resetear la m�sica
				menuPointer_ = 0;
				pointers_[0] = 0;
				pointers_[1] = 0;
				updateText();
			}
		}
	}
	//ir para atr�s
	else if (ownerPlayerBinder_->menuBack() && (menuPointer_ > 0))
	{
		SDL_Game::instance()->getAudioMngr()->playChannel(Resources::MenuBackward, 0);
		menuPointer_--;
		updateText();
	}
}

void MenuState::addRound(GamemodeID gMode, string map) {
	roundsVector_->push_back(std::make_pair(gMode, map));
}

void MenuState::onLoaded() { //poner el men� al principio
	SDL_Game::instance()->getAudioMngr()->playMusic(Resources::AudioId::MainMenuMusic, -1);
	menuPointer_ = 0;
	pointers_[0] = 0;
	pointers_[1] = 0;
	roundsVector_->clear();
	updateText();
}

void MenuState::updatePointer(int n) {
	int size = 0;

	if (menuPointer_ == 0) size = GamemodeID::NUMBER_OF_GAMEMODES + 1;
	else size = maps_.size();

	//moverse en el men� de manera modular
	pointers_[menuPointer_] += size + n;
	pointers_[menuPointer_] %= size;

	menuCursor_->setPosUIElement(b2Vec2(tinkyOffset_, (yOffset_ * (pointers_[menuPointer_] + 1)) - 35));
}

void MenuState::updateText() { //activar la pantalla actual y desactivar la otra, si solo hay dos no necesita m�s informaci�n
	menuCursor_->setPosUIElement(b2Vec2(tinkyOffset_, (yOffset_ * (pointers_[menuPointer_] + 1)) - 35));

	for (Entity* e : texts_[menuPointer_]) e->setActive(true); //activar actual
	for (Entity* e : texts_[1 - menuPointer_]) e->setActive(false); //desactivar otra
}

void MenuState::createText() { //preparar los textos
	int start, end, offset;

	for (int i = 0; i < 2; i++) {
		if (i == 0) {
			start = Resources::Capitalism;
			end = Resources::Exit;
		}
		else end = Resources::GardenRoomText;

		offset = start - 1;

		while (start <= end) {
			texts_[i].push_back(entityManager_->addEntity());
			texts_[i].back()->addComponent<UIViewer>(start, b2Vec2(xOffset_, (start - offset) * yOffset_), 1.5, 0);
			texts_[i].back()->setActive(false);
			start++;
		}
	}
}*/