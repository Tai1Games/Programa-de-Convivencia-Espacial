#pragma once
#include "Component.h"

class ThrownByPlayer : public Component
{
private:
	int lastOwner_ = -1;
	int timeWhenThrown_ = 0;
	double actTime_ = 0;
	double timeToDeleteOwner_ = 5;
	double sPerFrame_ = 0;

public:
	ThrownByPlayer(int playerId) :
		Component(ComponentType::ThrownByPlayer) {
		lastOwner_ = -1;
	}

	void init() override;
	void update() override;
	void throwObject(int playerId);
	inline int getOwnerId() const { return lastOwner_; }
};