#pragma once
#include "UIViewer.h"
#include "AbstractAnimatedViewers.h"

class AnimatedUIViewer : public UIViewer, public AbstractAnimatedViewers
{
public:
	AnimatedUIViewer(int textureId, int timeperframe, b2Vec2 pos, float scale, float angle) : UIViewer(textureId, pos, scale, angle) {
		timePerFrame_ = timeperframe;
	}
	virtual ~AnimatedUIViewer() {};

	virtual void init() override;
	virtual void update() override;
};
