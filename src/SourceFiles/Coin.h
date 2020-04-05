#pragma once
#include "Component.h"
#include "Viewer.h"
#include "Collider.h"
#include "Entity.h"
#include "b2_body.h"

class Coin : public Component
{
private:
	int value_ = 0;
	Viewer* vw_ = nullptr;
	Collider* col_ = nullptr;
public:
	Coin() : Component(ComponentType::Coin) {}
	~Coin() {};
	virtual void init() override;
	int getVal() { return value_; }
	void setVal(int v) { value_ = v; }
	void setActive(bool b, b2Vec2 pos = { 0,0 }, int value = 1);
};

