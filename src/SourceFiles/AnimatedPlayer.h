#pragma once
#include "Component.h"
#include "AdvancedAnimatedViewer.h"
#include "Hands.h"

class AnimatedPlayer : public AdvancedAnimatedViewer
{
private:
	int anim_ = 0; //animaci�n actual
	int skin_ = 0;

	Hands* hands = nullptr;

public:
	AnimatedPlayer(int textureId, int timePerFrame, int skin);

	virtual ~AnimatedPlayer();

	virtual void init() override;
	virtual void draw() const override;

	void setSkin(int skin) { skin_ = skin; };
	void resetAnimation() override;
};
