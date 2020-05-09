#pragma once
#include "Component.h"
#include "Collider.h"
#include "checkML.h"
#include "WiFiWavePool.h"

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
	WiFiWavePool* wifiPool_ = nullptr;

	double wifiWaveSpd_ = 10;
	int actFrame_ = 0;
	int frameWhenUpdate_ = 30;

public:
	RouterLogic(WiFightGameMode* gameMode, WiFiWavePool* wifiPool) :
		Component(ComponentType::RouterLogic),
		wifightGameMode_(gameMode),
		wifiPool_(wifiPool) {
	}
	~RouterLogic() {};
	void detectPlayer(Collider* playerDetected, int id);
	void loseContactPlayer(Collider* playerDetected, int id);
	virtual void init();
	virtual void update();
	virtual void onCollisionEnter(Collision* c);
	virtual void onCollisionExit(Collision* c);
	std::vector<PlayerInfo>* getPlayersInsideRange() { return &playersInsideRange_; };
};