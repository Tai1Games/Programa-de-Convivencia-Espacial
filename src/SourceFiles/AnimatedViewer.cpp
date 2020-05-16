#include "AnimatedViewer.h"

void AnimatedViewer::init() {
	Viewer::init();
	nFrames_ = tex_->getNumFramesX();
	AbstractViewers::setNFrames(nFrames_);
}

void AnimatedViewer::update()
{
	if (updateTime(nFrames_))
		frameX_ = frame_;
}