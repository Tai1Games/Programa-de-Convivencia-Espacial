#include "ControllerGameMode.h"
#include <map>

ControllerGameMode::~ControllerGameMode()
{
}

void ControllerGameMode::init(PlayState* game) {
	GameMode::init(game);
	GameMode::createPlayers(game);
	controller_ = ObjectFactory::makeController(state_->getEntityManager(), state_->getPhysicsWorld(), b2Vec2(tilemap_->getObjSpecialSpawnPos().x,
		tilemap_->getObjSpecialSpawnPos().y), b2Vec2(CONST(float, "CONTROLLER_W_PHYSICS"), CONST(float, "CONTROLLER_H_PHYSICS")));
	for (Entity* player : players_) controllerTimes_.push_back(0);

	GameMode::initProgressBars();

	ganador = state_->getEntityManager()->addEntity();

	ganador->addComponent<Transform>(SDL_Rect(), nullptr);
	ganador->addComponent<Viewer>();
	ganador->setActive(false);
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
		Viewer* v = GETCMP2(ganador, Viewer);
		v->setTexture(Resources::winner1 + winnerId_);
		v->setRenderRectangle({
			halfWidth_ - v->getTexture()->getWidth() / 2,
			halfHeight_,
			v->getTexture()->getWidth(),
			v->getTexture()->getHeight()
		});

		ganador->setActive(true);
	}
}