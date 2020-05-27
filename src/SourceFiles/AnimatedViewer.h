#pragma once
#include "Viewer.h"
#include "AbstractAnimatedViewers.h"

class AnimatedViewer : public Viewer, public AbstractAnimatedViewers
{
public:
	AnimatedViewer(int textureId, int timeperframe, ComponentType::CmpId componentId = ComponentType::Viewer) :
		Viewer(textureId, componentId) {
		timePerFrame_ = timeperframe;
	}

	~AnimatedViewer() {}

	virtual void init() override;
	virtual void update() override;
};
