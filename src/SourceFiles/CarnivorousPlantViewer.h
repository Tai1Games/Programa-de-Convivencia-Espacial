#pragma once
#include "AdvancedAnimatedViewer.h"
class CarnivorousPlantViewer : public AdvancedAnimatedViewer
{
private:
	int minFramesSpeed_ = 40;
	int framesUntilReopenMouth_ = 3;
	int frameClosedMouth_ = 2;

public:
	CarnivorousPlantViewer(int textureId, int timePerFrame);
	virtual ~CarnivorousPlantViewer();

	virtual void init() override;
	virtual void update() override;
};

