#include "EndGameState.h"
#include "SDL_Game.h"
#include "InputHandler.h"
#include "MatchInfo.h"
#include "GameStateMachine.h"
#include "Texture.h"
#include "SDLTexturesManager.h"
#include "Resources.h"

void EndGameState::init()
{
	backgroundT_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::RocketRoom);
}

void EndGameState::render()
{
	backgroundT_->render(0, 0);
	GameState::render();
}

void EndGameState::update()
{
	if (anyButtonPush) {
		GameStateMachine* gsMachine = SDL_Game::instance()->getStateMachine();
		gsMachine->transitionToState(States::menu);
	}
}

void EndGameState::handleInput()
{
	GameState::handleInput();
	InputHandler* ih = SDL_Game::instance()->getInputHandler();

	if (ih->keyDownEvent() || ih->isButonDownEvent()) {
		anyButtonPush = true;
	}
	else {
		anyButtonPush = false;
	}
}

void EndGameState::onLoaded()
{
	SDL_Game::instance()->getStateMachine()->deleteState(States::midGame);
}