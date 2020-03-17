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
	pauseText->addComponent<Viewer>(Resources::Pause,WINDOW_WIDTH/2,WINDOW_HEIGHT/2);

}

void PauseState::handleInput()
{
	GameState::handleInput();
	if (SDL_Game::instance()->getInputHandler()->isKeyUp(SDLK_ESCAPE)) {
		SDL_Game::instance()->getStateMachine()->changeToState(play);
	}
}
