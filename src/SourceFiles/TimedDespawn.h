#pragma once
#include "Entity.h"

class Weapon;

class TimedDespawn : public Component
{
private:
	int framesToDespawn_ = 0;
	int currentFrame_ = 0;
	bool activated = false;
	Weapon* weapon_ = nullptr;

public:
	TimedDespawn(int framesToDespawn) : Component(ComponentType::TimedDespawn) { framesToDespawn_ = framesToDespawn; }
	~TimedDespawn() {};
	void startTimer(Weapon* weapon);
	virtual void update();
};

