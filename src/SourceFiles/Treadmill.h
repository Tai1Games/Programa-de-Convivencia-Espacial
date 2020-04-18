#pragma once
#include "Component.h"
#include "Collider.h"
#include "Viewer.h"
#include "Entity.h"

class Treadmill :
	public Component
{
protected:
	Collider* myCol_ = nullptr;
	vector<b2Body*> objectsInside_;
	Viewer* myView_ = nullptr;
	float spinSpeed_;
	float launchSpeed_;
	float speedUp_;
	int frame_;
	int animationSpeed_;
	int totalFrames_;

public:
	Treadmill(Collider* c) :Component(ComponentType::Treadmill), myCol_(c){}
	void onCollisionEnter(Collision* c);
	void onCollisionExit(Collision* c);
	void update() override;
	void init() override;
};

