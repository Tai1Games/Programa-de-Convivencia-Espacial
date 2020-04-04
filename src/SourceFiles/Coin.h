#pragma once
#include "Component.h"
class Coin : public Component
{
private:
	int value_ = 0;
public:
	Coin(int val) : Component(ComponentType::Coin) { value_ = val; }
	~Coin() {};
	int getVal() { return value_; }
};

