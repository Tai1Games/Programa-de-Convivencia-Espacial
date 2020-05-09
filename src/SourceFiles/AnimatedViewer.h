#pragma once 
#include "Viewer.h"
#include "AbstractAnimatedViewers.h"

class AnimatedViewer : public Viewer, public AbstractAnimatedViewers
{

public:
	AnimatedViewer(int textureId, SDL_Rect clip, int timeperframe) : Viewer(textureId, clip) {
		timePerFrame_ = timeperframe;
	}

	~AnimatedViewer() {}

	virtual void init() override;
	virtual void update() override;
};

