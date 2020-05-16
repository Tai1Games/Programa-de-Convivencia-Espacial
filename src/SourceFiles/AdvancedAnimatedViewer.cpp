#include "AdvancedAnimatedViewer.h"

AdvancedAnimatedViewer::AdvancedAnimatedViewer(int textureId, int timePerFrame) :
	Viewer(textureId, ComponentType::AdvancedAnimatedViewer) {
	timePerFrame_ = timePerFrame;
}

AdvancedAnimatedViewer::~AdvancedAnimatedViewer()
{
}

void AdvancedAnimatedViewer::update()
{
	if (isPlaying_ && anim_ != -1 && updateTime(animationsInfo_[anim_].numFrames_)) {
		frameX_ = animationsInfo_[anim_].animOrigin_ + frame_;
		if (loops_ != -1 && currentLoop_ >= loops_) {	// para saber si hay que volver al idle
			resetAnimation();
		}
	}
}

void AdvancedAnimatedViewer::resetAnimation()
{
	startAnimation(-1, 0, -1, 0);
}