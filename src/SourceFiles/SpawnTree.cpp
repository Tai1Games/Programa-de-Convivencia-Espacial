#include "SpawnTree.h"

void SpawnTree::init() {
	spawnTime_ = CONST(double, "OBJECT_SPAWN_TIME");
	pixPerM_ = CONST(double, "PIXELS_PER_METER");
	sPerFrame_ = CONST(double, "SECONDS_PER_FRAME");
}

void SpawnTree::update() {
	timer_ += sPerFrame_;
	currentH_ = (objectH_ * timer_) / spawnTime_;
	currentW_ = (objectW_ * timer_) / spawnTime_;
	if (timer_ >= spawnTime_) SpawnObject();
}

void SpawnTree::draw() const {
	SDL_Rect rect;
	rect.x = spawnPos_.x; rect.y = spawnPos_.y;
	rect.w = currentW_; rect.h = currentH_;
	objectTex_->render(rect);
}