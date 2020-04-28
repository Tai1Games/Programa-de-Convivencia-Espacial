#pragma once
#include "Component.h"
#include "box2d.h"
#include "Collider.h"
#include "AttachesToObjects.h"
#include "PlayerData.h"
#include "checkML.h"
#include "InputBinder.h"


class PlayerController : public Component
{
private:
	bool chargingImpulse_ = false;
	Uint16 chargedFrames_;
	float impulseForce_;
	float chargeMultiplier_;
	float maxImpulseGrabbed_;
	float maxImpulseFloating_;


	int playerNumber_;
	b2Vec2 dirImpulse_;

	Collider* coll_ = nullptr;
	AttachesToObjects* attachesToObj_ = nullptr;
	PlayerData* playerData_ = nullptr;
	InputBinder* ib = nullptr;
public:
	PlayerController();
	virtual ~PlayerController() { Component::~Component(); };

	void init() override;
	void handleInput() override;
	void update() override;

	float getImpulseForce() { return impulseForce_; };
};

