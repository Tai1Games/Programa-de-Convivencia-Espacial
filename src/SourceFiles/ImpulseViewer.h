#pragma once
#include "Component.h"
#include "Resources.h"
#include "checkML.h"

class PlayerController;
class Collider;
class PlayerData;

class ImpulseViewer : public Component
{
protected:
	PlayerData* playerData_;
	Collider* playerCollider_;
	PlayerController* playerController_;

	int playerNumber_;
	int emptyTextureId_;
	int chargeTextureId_;

	Texture* emptyTexture_;
	Texture* chargeTexture_;
public:
	ImpulseViewer(int emptyTexId, int chargeTexId);
	virtual ~ImpulseViewer() { Component::~Component(); };

	void init() override;
	void draw() const override;
};
