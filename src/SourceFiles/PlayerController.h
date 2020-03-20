#pragma once
#include "Component.h"
#include "box2d.h"
#include "Collider.h"
#include "AttachesToObjects.h"
#include "PlayerData.h"


class PlayerController : public Component
{
private:
	float impulseForce_;
	b2Vec2 dirImpulse_;
	Collider* coll_ = nullptr;
	AttachesToObjects* attachesToObj_ = nullptr;
	PlayerData* playerData_ = nullptr;

public:
	PlayerController();
	~PlayerController() {}

	void init() override;
	void handleInput() override;

	void setForce(float f) { impulseForce_ = f; }
};

