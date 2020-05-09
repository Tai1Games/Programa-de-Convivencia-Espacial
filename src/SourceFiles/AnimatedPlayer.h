#pragma once
#include "Component.h"
#include "Viewer.h"

class AnimatedPlayer : public Viewer
{
private:
	int timeElapsed_ = 0;		//
	int timePerFrame_ = 20;		//medidos en frames

	int frame_ = 0;
	int anim_ = 0; //animación actual
	int skin_ = 0;
	vector<int> frameData_;	//numero de frames que tiene la animacion numero "indice del array"
	vector<int> cumFrameData_; //numero de frames TOTALES que preceden al primer frame de la animacion (algo parecido a una "frecuencia acumulada, pero de frames")
	int numFrames_ = 0;
	bool isPlaying_ = true;
	bool isLooping_ = false;

	int fWidth_ = 0;
	int fHeight_ = 0;

public:
	AnimatedPlayer(int textureId, int skin);

	~AnimatedPlayer();

	virtual void init() override;
	virtual void update() override;

	int getAnim() { return anim_; };
	bool getPlaying() { return isPlaying_; };
	bool getLooping() { return isLooping_; };

	void setSkin(int skin) { skin_ = skin; };
	void setAnim(int anim) { anim_ = anim; frame_ = 0; };
	void play();
	void pause();
	void stop();
};

