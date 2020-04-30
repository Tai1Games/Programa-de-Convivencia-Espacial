#include "BananaWeapon.h"

void BananaWeapon::action()
{
	std::cout << "Banana" << endl;
}

void BananaWeapon::setActive(bool a, b2Vec2 pos)
{
	entity_->setActive(a);
	GETCMP1_(Viewer)->setDrawable(a);
	GETCMP1_(Collider)->getBody()->SetEnabled(a);
	if (a) {
		GETCMP1_(Collider)->getBody()->SetTransform(pos, 0);
	}
}
