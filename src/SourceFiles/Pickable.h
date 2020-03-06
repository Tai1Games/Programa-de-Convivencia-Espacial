#pragma once
#include "Component.h"
#include "Entity.h"
#include "Collider.h"

class Pickable : public Component
{
private:
	Collider* mainCollider = nullptr;
	b2WeldJoint* joint = nullptr;
	bool picked = false;
protected:
public:
	Pickable(): Component(ComponentType::Pickable){}
	~Pickable(){};
	virtual void init() override;
	void PickedBy(Collider* player);
	bool IsPicked() { return picked; }
};

