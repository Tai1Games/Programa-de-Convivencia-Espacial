#include "Health.h"
#include <iostream>
#include "Collider.h"


Health::Health(int l) : Component(ComponentType::Health)
{
	lives_ = livesMax_ = l;
}

void Health::init() {
	col_ = GETCMP1_(Collider);
	col_->setUserData(this);
}

Health::~Health()
{
}

bool Health::subtractLife(int damage)
{
	lives_ -= damage;
	if (lives_ > 0) return true;
	else return false;
}

void Health::addLife(int sum)
{
	if (lives_ + sum > livesMax_) lives_ = livesMax_;
	else lives_ += sum;
}
