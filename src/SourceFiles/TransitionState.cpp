#include "TransitionState.h"
#include "SDL_Game.h"
#include "Resources.h"

TransitionState::TransitionState(int fromState, int toState, vector<GameState*>* gameStatesVector) :
	GameState(), currentState_(fromState), toState_(toState), gameStatesVector_(gameStatesVector) {
	blackSquare_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Debug);

	SDL_SetRenderDrawBlendMode(SDL_Game::instance()->getRenderer(), SDL_BLENDMODE_BLEND);

	transitionFrames_ = CONST(int, "SCENE_TRANSITION_FRAMES");
	WIN_WIDTH = CONST(int, "WINDOW_WIDTH");
	WIN_HEIGHT = CONST(int, "WINDOW_HEIGHT");
}

void TransitionState::update() {
	currentTransitionFrame_++;
	if (currentTransitionFrame_ == transitionFrames_ / 2)
		currentState_ = toState_;
}

void TransitionState::render() {
	if (currentTransitionFrame_ < transitionFrames_) {
		(*gameStatesVector_)[currentState_]->render();

		if (currentTransitionFrame_ <= transitionFrames_ / 2)
			SDL_SetRenderDrawColor(SDL_Game::instance()->getRenderer(), 0, 0, 0, 128);
		else
			SDL_SetRenderDrawColor(SDL_Game::instance()->getRenderer(), 0, 0, 0, 128);

		//blackSquare_->render({ 0,0,WIN_WIDTH,WIN_HEIGHT });
		SDL_Rect blackScreen = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
		SDL_RenderFillRect(SDL_Game::instance()->getRenderer(), &blackScreen);
		//SDL_SetRenderDrawColor(SDL_Game::instance()->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
	}
	else
	{
		SDL_Game::instance()->getStateMachine()->changeToState(currentState_);
	}
}