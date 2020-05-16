#pragma once
#include "AdvancedAnimatedViewer.h"
class CarnivorousPlantViewer : public AdvancedAnimatedViewer
{
private:
	int minFramesSpeed_ = 10;
	int frameCounter_ = 0;
	int framesUntilReopenMouth_ = 0;
	int frameClosedMouth_ = 2;
	bool opening_ = false;

public:
	CarnivorousPlantViewer(int textureId, int timePerFrame);
	virtual ~CarnivorousPlantViewer();

	virtual void init() override;
	virtual void update() override;
};

