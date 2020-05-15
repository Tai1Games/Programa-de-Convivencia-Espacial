#include "AbstractAnimatedViewers.h"

bool AbstractAnimatedViewers::updateTime(int nFrames)
{
	if (activeAnimation_) {

		timeElapsed_++;		//Aumentamos en uno el número de ciclos

		if (timeElapsed_ >= timePerFrame_) {
			timeElapsed_ = 0;	//Reseteamos el contador de frames

			if ((++frame_) >= nFrames) {
				frame_ %= nFrames;
				++currentLoop_;
				if (loops_ != -1 && currentLoop_ > loops_) {
					stopAnimation();
					return false;
				}
			}
			return true;
		}
	}
	return false;
}
