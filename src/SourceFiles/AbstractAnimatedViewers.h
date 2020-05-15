#pragma once
class AbstractAnimatedViewers
{
protected:
	int frame_ = 0;
	int timeElapsed_ = 0;
	int timePerFrame_ = 0;
	int currentLoop_ = 0;
	bool updateTime(int nFrames);

public:
	struct AnimationInfo {
		short unsigned int animOrigin_;
		short unsigned int numFrames_;
	};
};

