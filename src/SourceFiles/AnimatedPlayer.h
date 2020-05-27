#pragma once
#include "Component.h"
#include "AdvancedAnimatedViewer.h"

class AnimatedPlayer : public AdvancedAnimatedViewer
{
private:
	int anim_ = 0; //animación actual
	int skin_ = 0;

public:
	AnimatedPlayer(int textureId, int timePerFrame, int skin);

	virtual ~AnimatedPlayer();

	virtual void init() override;

	void setSkin(int skin) { skin_ = skin; };
	void resetAnimation() override;
};
