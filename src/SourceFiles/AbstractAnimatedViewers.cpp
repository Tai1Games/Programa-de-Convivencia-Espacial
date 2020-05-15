#include "AbstractAnimatedViewers.h"

bool AbstractAnimatedViewers::updateTime(int nFrames)
{
	timeElapsed_++;		//Aumentamos en uno el número de ciclos

	if (timeElapsed_ >= timePerFrame_) {
		timeElapsed_ = 0;	//Reseteamos el contador de frames

		if ((++frame_) >= nFrames) {
			frame_ %= nFrames;
			++currentLoop_;
		}
		return true;
	}
	return false;
}
