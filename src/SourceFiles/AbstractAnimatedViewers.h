#pragma once
class AbstractAnimatedViewers
{
protected:
	int frame_ = 0;
	int timeElapsed_ = 0;
	int timePerFrame_ = 0;
	int loops_ = -1;
	int currentLoop_ = 0;
	bool activeAnimation_ = true;
	bool isPlaying_ = true;

	bool updateTime(int nFrames);

public:
	struct AnimationInfo {
		short unsigned int animOrigin_;
		short unsigned int numFrames_;
	};

	// animation aquí sólo sirve para el override
	virtual void startAnimation(int loops = -1, int animation = 0) {
		activeAnimation_ = true;
		loops_ = loops;
	}

	void pauseAnimation()
	{
		isPlaying_ = false;
	}
	

	void resumeAnimation()
	{
		isPlaying_ = true;
	}

	virtual void stopAnimation() {
		activeAnimation_ = false;
		frame_ = 0;
	}

	void setAnimSpeed(int timePerFrame) {
		timePerFrame_ = timePerFrame;
	}

};