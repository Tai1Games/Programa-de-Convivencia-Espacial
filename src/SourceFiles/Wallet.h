#pragma once
#include "Component.h"
#include "Collider.h"

class Wallet : public Component
{
private:
	int numCoins_ = 0;
	Collider* collPlayer_ = nullptr;
public:
	Wallet() : Component(ComponentType::Wallet) {};
	~Wallet() {};
	virtual void init() override;
	void dropCoins(int n);
	void addCoins(int n) { numCoins_ += n; }
};

