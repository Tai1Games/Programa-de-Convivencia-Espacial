#pragma once
#include "Component.h"
#include "checkML.h"
#include "Viewer.h"

class Pad:public Component
{
private:
	Viewer* viewer_;
	bool onAnimation_;
	int frame_;
public:
	Pad();
	virtual ~Pad();

	void init() override;
	void update() override;
	void startAnim();
};

