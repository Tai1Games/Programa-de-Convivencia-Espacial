#pragma once
#include "Entity.h"
#include "Collider.h"
class AttachesToObjects : public Component
{
private:
	Collider* attachedObject = nullptr;
	Collider* mainCollider = nullptr;
public:
	AttachesToObjects() : Component(ComponentType::AttachesToObjects) {};
	~AttachesToObjects() {};
	void attachToObject(Collider* attachableObject);
	void releaseFromObject() { attachedObject = nullptr; }
	virtual void init() override;
	virtual void update() override;
};

