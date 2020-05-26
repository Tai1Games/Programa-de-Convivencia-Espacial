#pragma once
#include "AnimatedViewer.h"
#include "Resources.h"
#include "checkML.h"

class PlayerController;
class Collider;
class PlayerData;
class InputBinder;

class ImpulseViewer : public AnimatedViewer
{
protected:
	PlayerData* playerData_;
	Collider* playerCollider_;
	PlayerController* playerController_;
	InputBinder* ib_;

	//constants
	float maxImpulseGrabbed_;
	int impulseSize_;

	int emptyTextureId_;
	int chargeTextureId_;

	int numFramesCharge_ = 0;

	float angle_ = 0;

	Texture* emptyTexture_;
	Texture* chargeTexture_;
public:
	ImpulseViewer(int emptyTexId, int chargeTexId);
	virtual ~ImpulseViewer() { };

	void init() override;
	void update() override;
	void draw() const override;
};
