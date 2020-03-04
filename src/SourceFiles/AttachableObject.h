#pragma once
#include "Entity.h"
#include "box2d.h"
class AttachableObject : public Component
{
private:
	AttachableObject() : Component(ComponentType::AttachableObject) {};
	~AttachableObject() {};
public:
};

