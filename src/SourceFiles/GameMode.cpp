#include "GameMode.h"
#include "PlayState.h"

void GameMode::init(PlayState* game) {
	players_ = game->getPlayers();
}