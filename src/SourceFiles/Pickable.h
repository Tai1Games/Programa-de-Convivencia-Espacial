#pragma once
#include "Component.h"
#include "Entity.h"
#include "Collider.h"

class Pickable : public Component
{
private:
	Collider* mainCollider_ = nullptr;
	b2WeldJoint* joint_ = nullptr;
	bool picked_ = false;
protected:
public:
	Pickable(): Component(ComponentType::Pickable){}
	~Pickable(){};
	virtual void init() override;
	void PickObjectBy(Collider* player);
	bool IsPicked() { return picked_; }
	void UnPickObject();
};

