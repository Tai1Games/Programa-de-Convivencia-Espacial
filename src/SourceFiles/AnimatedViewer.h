#pragma once 
#include "Component.h"
#include "Viewer.h"

class AnimatedViewer : public Viewer
{
private:
	int frame = 0;
	int nframes = 0;
	int time = 0;
	int timeFrame = 0;
public:
	AnimatedViewer(int textureId, SDL_Rect clip, int timeframe) : Viewer(textureId) {
		timeFrame = timeframe;
		clip_ = clip;
	}

	~AnimatedViewer() {}

	virtual void init() override;
	virtual void update() override;
	virtual void onCollisionEnter(Collision* c) {};
	virtual void onCollisionExit(Collision* c) {};
};

