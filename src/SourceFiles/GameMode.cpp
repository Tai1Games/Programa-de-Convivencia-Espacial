#include "GameMode.h"

void GameMode::init(PlayState* game) {
	players_ = game->getPlayers();
}