#pragma once
#include "Component.h"
#include "Collider.h"

//#include "SDL_Game.h"

class Entity;
class CapitalismGameMode;

class Wallet : public Component
{
private:
	int numCoins_ = 10;
	Collider* collPlayer_ = nullptr;
	CapitalismGameMode* gameMode_ = nullptr;
public:
	Wallet(CapitalismGameMode* gamemode) : Component(ComponentType::Wallet) { gameMode_ = gamemode; };
	~Wallet() {};
	virtual void init() override;
	void dropCoins(int damage);
	void addCoins(int n) { numCoins_ += n; cout << "HE RECOGIDO " << n << endl; }
};

