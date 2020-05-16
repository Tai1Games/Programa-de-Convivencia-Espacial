#pragma once
#include "Component.h"
#include "checkML.h"
#include "AnimatedViewer.h"

class Pad:public Component
{
private:
	AnimatedViewer* viewer_;
public:
	Pad() {};
	virtual ~Pad() {};

	virtual void init() override;
	virtual void onCollisionExit(Collision* c);
};

