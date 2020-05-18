#include "AnimatedUIViewer.h"

void AnimatedUIViewer::init() {
	UIViewer::init();
	nFrames_ = tex_->getNumFramesX();
	setNFrames(nFrames_);
}

void AnimatedUIViewer::update() {
	if (updateTime(nFrames_))
		frameX_ = frame_;
}
