#pragma once 
#include "Component.h"
#include "Viewer.h"

class AnimatedViewer : public Viewer
{
private:
	int frame_ = 0;
	int timeElapsed_ = 0;
	int timePerFrame_ = 0;
public:
	AnimatedViewer(int textureId, SDL_Rect clip, int timeperframe) : Viewer(textureId, clip) {
		timePerFrame_ = timeperframe;
	}

	AnimatedViewer(int textureId, SDL_Rect clip, int timeperframe, b2Vec2 pos, float scale, float angle) : Viewer(textureId, pos, scale, angle, clip){
		timePerFrame_ = timeperframe;
	}

	~AnimatedViewer() {}

	virtual void init() override;
	virtual void update() override;
};

