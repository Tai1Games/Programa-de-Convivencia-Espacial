#include "Bullet.h"

void Bullet::init()
{
	col_ = GETCMP1_(Collider);
	viewer_ = GETCMP1_(Viewer);
}

void Bullet::setActive(bool a, b2Vec2 pos, b2Vec2 size, int texture, int damage)
{
	entity_->setActive(a);
	viewer_->setDrawable(a);
	col_->getBody()->SetEnabled(a);

	if (a) { //hacer movidas
		col_->getBody()->SetTransform(pos,0);
		//SIZE------------
		viewer_->setTexture(texture);
		damage_ = damage;
	}
}
