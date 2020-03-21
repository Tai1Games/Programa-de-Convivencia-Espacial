#include "GameMode.h"
#include "PlayState.h"

void GameMode::init(PlayState* state) {
	state_ = state;
	players_ = state->getPlayers();
}