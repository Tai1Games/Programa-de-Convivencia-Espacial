#pragma once
#include "Component.h"
#include "Collider.h"
#include "Viewer.h"

class Bullet: public Component
{
private:
	Collider* col_;
	Viewer* viewer_;
	int damage_ = 0;

public:
	Bullet():Component(ComponentType::Bullet){}
	~Bullet(){}

	virtual void init();
	virtual void setActive(bool a, b2Vec2 pos = { 0,0 }, b2Vec2 size = { 0,0 }, int texture = 0, int damage = 0);
};

