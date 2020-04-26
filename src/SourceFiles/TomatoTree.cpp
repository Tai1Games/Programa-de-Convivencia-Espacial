/*#include "TomatoTree.h"
#include "Collider.h"
#include "ObjectFactory.h"

void TomatoTree::init() {
	SpawnTree::init();
	SpawnTree::objectW_ = (int)(CONST(double, "BALL_X") * pixPerM_);
	SpawnTree::objectH_ = (int)(CONST(double, "BALL_Y") * pixPerM_);
	Collider* coll = GETCMP1_(Collider);
	SDL_Rect rectRender = coll->getRectRender();
	double spawnPosX = rectRender.x + (rectRender.w / 2) - (objectTex_->getWidth() / 2);
	double spawnPosY = rectRender.y + -(objectTex_->getHeight());
	SpawnTree::spawnPos_ = b2Vec2(spawnPosX, spawnPosY);
}

void TomatoTree::SpawnObject() {
	pool_->addTomato(b2Vec2((spawnPos_.x / pixPerM_), (CONST(double, "WINDOW_HEIGHT") - spawnPos_.y) / pixPerM_));
}*/