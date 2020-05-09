#pragma once
#include "UIViewer.h"
#include "AbstractAnimatedViewers.h"

class AnimatedUIViewer : public UIViewer, AbstractAnimatedViewers
{
public:
	AnimatedUIViewer(int textureId, SDL_Rect clip, int timeperframe, b2Vec2 pos, float scale, float angle) : UIViewer(textureId, pos, scale, angle, clip){
		timePerFrame_ = timeperframe;
	}
	~AnimatedUIViewer() {};

	virtual void init() override;
	virtual void update() override;
};

