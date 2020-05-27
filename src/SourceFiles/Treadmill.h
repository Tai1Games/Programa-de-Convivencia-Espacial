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
	float spinSpeed_ = 0;
	float launchSpeed_ = 0;
	float speedUp_ = 0;

public:
	Treadmill(Collider* c) :Component(ComponentType::Treadmill), myCol_(c) {}
	void onCollisionEnter(Collision* c);
	void onCollisionExit(Collision* c);
	void update() override;
	void init() override;
};
