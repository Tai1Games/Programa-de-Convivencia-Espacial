#pragma once
#include "Component.h"
#include "Constants.h"
class ProgressBar : public Component
{
private:
	int actualProgress_ = 0;
public:
	ProgressBar(): Component(ComponentType::ProgressBar) {};
	~ProgressBar() {}
	bool addPoints(int sum);
	int getPlayerProgress() { return actualProgress_; }
};

