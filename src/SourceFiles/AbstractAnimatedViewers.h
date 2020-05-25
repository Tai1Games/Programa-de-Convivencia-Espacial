#pragma once
class AbstractAnimatedViewers
{
protected:
	int frame_ = 0;					// the current frame of the animation
	int limitFrame_ = -1;			// the max frame that the animation can reach (-1 = no limit)
	int timeElapsed_ = 0;			// number of frames passed since the last animation update
	int timePerFrame_ = 0;			// frames number of frames it takes to go to the next frame
	int loops_ = -1;				// amount of repetitions (-1 = loop until stopped)
	int currentLoop_ = 0;			// current repetition
	bool activeAnimation_ = true;	// does it have to animate?
	bool isPlaying_ = true;			// is it paused?
	int baseSpeed_ = 10;			// initial speed

	// Calculates if time passed for the next frame
	// and advances the frame if that's the case.
	// Also takes in account the number of loops that
	// should be played and the number of frames in the
	// animation.
	// int nFrames = frames that the animation contains
	bool updateTime(int nFrames);

public:
	// Represents a single animation in the
	// context of a spriteSheet. Contains
	// information about where the animation
	// starts and how many frames it has.
	struct AnimationInfo {
		short unsigned int animOrigin_;
		int numFrames_;
	};

	// Starts a new animation that lasts "loops"
	// times (-1 = loop until stopped) from the frame
	// 'frame' until the frame 'limitFrame'.
	// Ignore the 'animation' field, it is used for inheritance.
	virtual void startAnimation(int loops = -1, int initialFrame = 0, int limitFrame = -1, int animation = 0) {	// animation aqu� s�lo sirve para el override
		stopAnimation();
		timeElapsed_ = 0;
		frame_ = initialFrame;
		limitFrame_ = limitFrame;
		activeAnimation_ = true;
		loops_ = loops;
		currentLoop_ = 0;
	}

	// Pauses the current animation in the current frame
	void pauseAnimation() {
		isPlaying_ = false;
	}
	
	// Resumes the animation at the current frame.
	// Does nothing if animation was not paused.
	void resumeAnimation()
	{
		isPlaying_ = true;
	}

	// Stops the current animation and resets
	// the frame. Usually used when another animation
	// wants to be played.
	virtual void stopAnimation() {
		activeAnimation_ = false;
		frame_ = 0;
	}

	// Changes the number of frames it takes to
	// go to the next frame.
	void setAnimSpeed(int timePerFrame) {
		timePerFrame_ = timePerFrame;
	}
};