#include "TransitionState.h"
#include "SDL_Game.h"
#include "Resources.h"

TransitionState::TransitionState(int fromState, int toState, vector<GameState*>* gameStatesVector) :
	GameState(), currentState_(fromState), toState_(toState), gameStatesVector_(gameStatesVector) {

	SDL_SetRenderDrawBlendMode(SDL_Game::instance()->getRenderer(), SDL_BLENDMODE_BLEND);

	transitionFrames_ = CONST(int, "SCENE_TRANSITION_FRAMES");
	WIN_WIDTH = CONST(int, "WINDOW_WIDTH");
	WIN_HEIGHT = CONST(int, "WINDOW_HEIGHT");

	frameToAlphaRatio_ = 255 / transitionFrames_;
	blackScreen_ = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
}

void TransitionState::update() {
	currentTransitionFrame_++;
	if (currentTransitionFrame_ == transitionFrames_)
		currentState_ = toState_;
}

void TransitionState::render() {
	if (currentTransitionFrame_ < transitionFrames_ * 2) {
		(*gameStatesVector_)[currentState_]->render();
		if (currentTransitionFrame_ <= transitionFrames_)
			SDL_SetRenderDrawColor(SDL_Game::instance()->getRenderer(), 0, 0, 0, currentTransitionFrame_ * frameToAlphaRatio_);
		else {
			SDL_SetRenderDrawBlendMode(SDL_Game::instance()->getRenderer(), SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(SDL_Game::instance()->getRenderer(), 0, 0, 0, 255 - (currentTransitionFrame_ - transitionFrames_) * frameToAlphaRatio_);
		}

		
		SDL_RenderFillRect(SDL_Game::instance()->getRenderer(), &blackScreen_);
	}
	else
	{
		SDL_SetRenderDrawColor(SDL_Game::instance()->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_SetRenderDrawBlendMode(SDL_Game::instance()->getRenderer(), SDL_BLENDMODE_NONE);
		SDL_Game::instance()->getStateMachine()->changeToState(currentState_);
	}
}