#pragma once
#include "Component.h"

class Collider;
class Hands;
class Viewer;

class TomatoLogic : public Component
{
private:
	Collider* colTomato_ = nullptr;
	Hands* playerHands_ = nullptr;
	Viewer* tomatoViewer_ = nullptr;

	bool activated_ = false;
	bool exploded_ = false;
	bool STOPYAJODER_ = false;
	int timeActivated_ = 0;
	int timeExploded_ = 0;
	int frame = 0;
	//Constants loaded in Init()

	int timeForExplosion_ = 0;
	int timeForExplosionExpire_ = 0;
	int nFramesCharge_ = 0;
	int nFramesExplosion_ = 0;
	int frameSpeedCharge_ = 0;
	int frameSpeedExplosion_ = 0;
	int frameSize_ = 0;
public:
	TomatoLogic() : Component(ComponentType::TomatoLogic){};
	~TomatoLogic() {};

	virtual void init();
	virtual void update();
	virtual void handleInput(); //DEBUG
	virtual void onCollisionEnter(Collision* c);
};

