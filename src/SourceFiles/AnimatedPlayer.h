#pragma once
#include "Component.h"
#include "Viewer.h"
#include "AbstractAnimatedViewers.h"

class AnimatedPlayer : public Viewer, public AbstractAnimatedViewers
{
private:
	int anim_ = 0; //animación actual
	int skin_ = 0;
	//vector<int> frameData_;	//numero de frames que tiene la animacion numero "indice del array"
	//vector<int> cumFrameData_; //numero de frames TOTALES que preceden al primer frame de la animacion (algo parecido a una "frecuencia acumulada, pero de frames")
	vector<AnimationInfo> animationsInfo_;

	//int fWidth_ = 0;
	//int fHeight_ = 0;

public:
	AnimatedPlayer(int textureId, int timePerFrame, int skin);

	~AnimatedPlayer();

	virtual void init() override;
	virtual void update() override;

	void setSkin(int skin) { skin_ = skin; };

	virtual void startAnimation(int loops = -1, int animation = 0) override {
		anim_ = animation;
		activeAnimation_ = true;
		loops_ = loops;
		frame_ = 0;
	}

	virtual void resetAnimation();
};

