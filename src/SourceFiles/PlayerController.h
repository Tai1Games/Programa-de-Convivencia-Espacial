#pragma once
#include "Component.h"
#include "box2d.h"
#include "Collider.h"
#include "AttachesToObjects.h"
#include "PlayerData.h"


class PlayerController : public Component
{
private:
	Uint32 chargeTimeStart_;

	int playerNumber_;
	b2Vec2 dirImpulse_;

	Collider* coll_ = nullptr;
	AttachesToObjects* attachesToObj_ = nullptr;
	PlayerData* playerData_ = nullptr;
public:
	PlayerController();
	virtual ~PlayerController() { Component::~Component(); };

	void init() override;
	void handleInput() override;

	float calculateForce();
};

