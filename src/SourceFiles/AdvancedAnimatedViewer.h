#pragma once
#include "Component.h"
#include "Viewer.h"
#include "AbstractAnimatedViewers.h"

class AdvancedAnimatedViewer : public Viewer, public AbstractAnimatedViewers
{
protected:
	int anim_ = 0; //animación actual
	vector<AnimationInfo> animationsInfo_;

public:
	AdvancedAnimatedViewer(int textureId, int timePerFrame);

	~AdvancedAnimatedViewer();

	// make sure to load frames as in AnimatedPlayer.cpp
	virtual void init() override = 0;
	virtual void update() override;

	virtual void startAnimation(int loops = -1, int initialFrame = 0, int limitFrame = -1, int animation = 0) override {
		stopAnimation();
		anim_ = animation;
		activeAnimation_ = true;
		loops_ = loops;
		frame_ = initialFrame;
		limitFrame_ = limitFrame;
	}

	virtual void resetAnimation();
};