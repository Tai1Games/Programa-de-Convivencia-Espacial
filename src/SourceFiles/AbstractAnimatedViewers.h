#pragma once
class AbstractAnimatedViewers
{
protected:
	int frame_ = 0;
	int timeElapsed_ = 0;
	int timePerFrame_ = 0;
public:
	AbstractAnimatedViewers() {};
	~AbstractAnimatedViewers() {};

	bool updateTime(int nFrames);
};

