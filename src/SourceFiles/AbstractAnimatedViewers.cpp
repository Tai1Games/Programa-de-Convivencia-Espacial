#include "AbstractAnimatedViewers.h"

bool AbstractAnimatedViewers::updateTime(int nFrames)
{
	timeElapsed_++;		//Aumentamos en uno el número de ciclos

	if (timeElapsed_ == timePerFrame_) {
		timeElapsed_ = 0;	//Reseteamos el contador de frames

		frame_ = frame_ % nFrames;
		return true;
	}
	return false;
}
