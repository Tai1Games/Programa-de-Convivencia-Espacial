#include "CreditsState.h"
#include "PlayableMenuState.h"
#include "Transform.h"
#include "AttachesToObjects.h"
#include "Texture.h"
#include "Viewer.h"
#include "InputBinder.h"
#include "ObjectFactory.h"
#include "PlayerData.h"
#include "GameStateMachine.h"
#include "Component.h"

#include "PlayerFactory.h"
#include "UIViewer.h"


CreditsState::~CreditsState()
{
	delete entityManager_;		entityManager_ = nullptr;
}

void CreditsState::init()
{
	entityManager_ = new EntityManager();

	secondsPerFrame_ = CONST(double, "SECONDS_PER_FRAME");

	//FONDO
	fondo_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::CreditsRoom);

	//MÚSICA
	//SDL_Game::instance()->getAudioMngr()->playMusic(Resources::MainMenuMusic, -1);

	//Texto para terminar la intermision
	continueText = entityManager_->addEntity();
	continueText->addComponent<UIViewer>(Resources::ContinueText, b2Vec2((CONST(int, "WINDOW_WIDTH") / 2) - 600, CONST(int, "WINDOW_HEIGHT") - 130), 1, 0);
}

void CreditsState::update()
{
	GameState::update();
}

void CreditsState::render()
{
	fondo_->render(0, 0);
	GameState::render();
}

void CreditsState::handleInput()
{
	GameState::handleInput();

	InputHandler* ih = SDL_Game::instance()->getInputHandler();
	if (ih->keyDownEvent() || ih->isButonDownEvent()) {
		GameStateMachine* gsMachine = SDL_Game::instance()->getStateMachine();
		gsMachine->transitionToState(States::playableMenu);
	}

}

void CreditsState::onLoaded()
{
	//player->getComponent<Collider>(ComponentType::Collider)->setTransform(b2Vec2(tmap->getPlayerSpawnPoint(0).x, tmap->getPlayerSpawnPoint(0).y), 0);
}
