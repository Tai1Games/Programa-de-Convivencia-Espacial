#include "Health.h"
#include <iostream>

Health::Health(int l) : Component(ComponentType::Health)
{
	lifes_ = lifesMax_ = l;
}

Health::~Health()
{
}

bool Health::subtractLife(int damage)
{
	lifes_ -= damage;

	if (lifes_ > 0) return true;
	else return false;
}

void Health::addLife(int sum)
{
	if (lifes_ + sum > lifesMax_) lifes_ = lifesMax_;
	else lifes_ += sum;
}
