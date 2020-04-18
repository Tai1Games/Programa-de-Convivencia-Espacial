#pragma once
#include "Component.h"
#include "Collider.h"

//#include "SDL_Game.h"

class Entity;
class CapitalismGameMode;

class Wallet : public Component
{
private:
	int numCoins_ = 0; //Se asigna en init.
	int coinBaseSize_ = 0; //Se asigna en init.
	Collider* collPlayer_ = nullptr;
	CapitalismGameMode* gameMode_ = nullptr;
public:
	Wallet(CapitalismGameMode* gamemode) : Component(ComponentType::Wallet) { gameMode_ = gamemode; };
	~Wallet() {};
	virtual void init() override;
	void dropCoins(int damage, int player);
	void addCoins(int n) { numCoins_ += n; cout << "HE RECOGIDO " << n << endl; }
	int getCoins() { return numCoins_; }

	virtual void onCollisionEnter(Collision* c);
};

