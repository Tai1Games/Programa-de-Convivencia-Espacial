#pragma once
#include "Component.h"
#include "TimeGameMode.h"

class ThrownByPlayer : public Component
{
private:
	int lastOwner_ = -1;
	int timeWhenThrown_ = 0;
	double actTime_ = 0;
	double timeToDeleteOwner_ = 5;
	double sPerFrame_ = 0;
	TimeGameMode* gameMode_ = nullptr;

public:
	ThrownByPlayer(TimeGameMode* gameMode) :
		Component(ComponentType::ThrownByPlayer),gameMode_(gameMode) {
		lastOwner_ = -1;
	}

	void init() override;
	void update() override;
	void throwObject(int playerId);
	inline int getOwnerId() const { return lastOwner_; }
	void addPointsToOwner();
};