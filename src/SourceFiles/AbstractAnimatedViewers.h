#pragma once
class AbstractAnimatedViewers
{
protected:
	int frame_ = 0;
	int timeElapsed_ = 0;
	int timePerFrame_ = 0;
	int loops_ = -1;
	int currentLoop_ = 0;
	bool updateTime(int nFrames);
	bool activeAnimation_ = true;

public:
	struct AnimationInfo {
		short unsigned int animOrigin_;
		short unsigned int numFrames_;
	};

	void startAnimation(int loops = -1) {
		activeAnimation_ = true;
		loops_ = loops;
	}

	void stopAnimation() {
		activeAnimation_ = false;
		frame_ = 0;
	}
};