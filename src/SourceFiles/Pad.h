#pragma once
#include "Component.h"
#include "checkML.h"

class Pad:public Component
{
private:


public:
	Pad();
	virtual ~Pad();

	void init() override;
};

