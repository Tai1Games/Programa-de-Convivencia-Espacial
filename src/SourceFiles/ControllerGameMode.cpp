#include "ControllerGameMode.h"
#include <map>

ControllerGameMode::~ControllerGameMode()
{

}

void ControllerGameMode::init(PlayState* game)  {
	GameMode::init(game);
	GameMode::createPlayers(game);
	controller_ = ObjectFactory::makeController(state_->getEntityManager(), state_->getPhysicsWorld(), b2Vec2(tilemap_->getObjSpecialSpawnPos().x, 
		tilemap_->getObjSpecialSpawnPos().y), b2Vec2(CONST(float, "CONTROLLER_W_PHYSICS"), CONST(float, "CONTROLLER_H_PHYSICS")));
	for (Entity* player : players_) controllerTimes_.push_back(0);
	
	GameMode::initProgressBars();
}

void ControllerGameMode::update() {
	if (!roundFinished_) {
		if (controller_->IsPicked()) {
			controllerTimes_[controller_->getPlayerId()] += (CONST(double, "MS_PER_FRAME"));
			if (controllerTimes_[controller_->getPlayerId()] >= CONST(double, "TIME_TO_WIN")) {
				roundFinished_ = true;
				winnerId_ = controller_->getPlayerId();
			}
		}
	}
	GameMode::update();
}


void ControllerGameMode::render() {
	GameMode::renderProgressBars(controllerTimes_, CONST(double, "TIME_TO_WIN"));
	
	if (roundFinished_) {
		Texture* ganador = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::winner1 + winnerId_);
		ganador->render(CONST(int, "WINDOW_WIDTH")/2 - ganador->getWidth() * 0.5, CONST(int, "WINDOW_HEIGHT")/2);
	}
}
