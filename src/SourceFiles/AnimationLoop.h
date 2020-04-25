#pragma once
#include "Component.h"
#include "Viewer.h"

class AnimationLoop : public Component
{
private:
	int start=0;
	int frame = 0;
	int nframes = 0;
	int speed = 0;
	SDL_Rect clip;
	Viewer* image = nullptr;
public:
	AnimationLoop(int frames_, int animationSpeed, SDL_Rect clip_) : Component(ComponentType::AnimationLoop) {
		nframes = frames_;
		speed = animationSpeed;
		clip = clip_;
	}

	~AnimationLoop() { image = nullptr; }

	virtual void init() override;
	virtual void update() override;
	virtual void onCollisionEnter(Collision* c) {};
	virtual void onCollisionExit(Collision* c) {};
};

