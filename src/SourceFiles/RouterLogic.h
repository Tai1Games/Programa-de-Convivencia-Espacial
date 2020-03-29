#pragma once
#include "Component.h"
#include "Collider.h"

class WiFightGameMode;

class RouterLogic : public Component
{
private:
	struct PlayerInfo {
		int id;
		Collider* posPlayer = nullptr;
	};
	vector<PlayerInfo> playersInsideRange_;
	Collider* posRouter_ = nullptr;
	WiFightGameMode* wifightGameMode_ = nullptr;

public:
	RouterLogic(WiFightGameMode* gameMode) : Component(ComponentType::RouterLogic) { wifightGameMode_ = gameMode; };
	~RouterLogic() {};
	void detectPlayer(Collider* playerDetected, int id);
	void loseContactPlayer(Collider* playerDetected, int id);
	virtual void init();
	virtual void update();
};