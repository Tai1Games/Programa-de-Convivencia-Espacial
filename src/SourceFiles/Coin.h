#pragma once
#include "Component.h"
#include "Viewer.h"
#include "Collider.h"
#include "Entity.h"
#include "b2_body.h"

class Coin : public Component
{
private:
	int value_ = 0;
	int justDroppedByPlayer_ = -1;
	double timeSinceDropped_ = 0;
	Viewer* vw_ = nullptr;
	Collider* col_ = nullptr;

	//Load of constants
	int winWidth_ = 0;
	int winHeigth_ = 0;
	int pixelsPerMeter_ = 0;
	int repickeableTime_ = 0;
	double sPerFrame_ = 0;

public:
	Coin() : Component(ComponentType::Coin) {}
	~Coin() {};
	virtual void init() override;
	virtual void update();
	int getVal() { return value_; }
	int getPlayerDropped() { return justDroppedByPlayer_; }
	void setVal(int v) { value_ = v; }
	void setActive(bool b, int droppedByPlayerNum = -1, b2Vec2 pos = { 0,0 }, int value = 1);
};

