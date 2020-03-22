#pragma once
#include "Component.h"
#include "box2d.h"
#include "Collider.h"
#include "AttachesToObjects.h"



class PlayerController : public Component
{
private:
	b2Vec2 dirImpulse_;
	Collider* coll_;
	AttachesToObjects* attachesToObj_;
	float impulseForce_;
	int playerNumber_;//Número del jugador (de 1 a 4));
	Uint32 chargeTimeStart_;
public:
	PlayerController(int p);
	virtual ~PlayerController() { Component::~Component(); };

	void init() override;
	void handleInput() override;

	void setForce(float f) { impulseForce_ = f; }
	float calculateForce();
};

