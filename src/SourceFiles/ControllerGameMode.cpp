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
			controllerTimes_[controller_->getPlayerId()] += msPerFrame_;
			if (controllerTimes_[controller_->getPlayerId()] >= timeToWin_) {
				roundFinished_ = true;
				winnerId_ = controller_->getPlayerId();
			}
		}
	}
	GameMode::update();
}


void ControllerGameMode::render() {
	GameMode::renderProgressBars(controllerTimes_, timeToWin_);
	
	if (roundFinished_) {
		string winMsg = "Gana el jugador " + to_string(winnerId_+1);
		Texture ganador(SDL_Game::instance()->getRenderer(), winMsg,
			SDL_Game::instance()->getFontMngr()->getFont(Resources::NES_Chimera), { COLOR(0xffffffff) });
		SDL_Rect destRect {
			halfWidth_ - ganador.getWidth() / 2,
			halfHeight_,
			ganador.getWidth(),
			ganador.getHeight()
		};
		ganador.render(destRect, 0, 0);
	}
}
