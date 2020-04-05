#include "GameMode.h"
#include "PlayState.h"
#include "HealthViewer.h"

GameMode::~GameMode() {}

void GameMode::init(PlayState* state) {
	state_ = state;
	players_ = state->getPlayers();
}