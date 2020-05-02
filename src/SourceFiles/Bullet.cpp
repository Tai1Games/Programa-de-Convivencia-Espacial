#include "Bullet.h"

void Bullet::init()
{
	col_ = GETCMP1_(Collider);
	viewer_ = GETCMP1_(Viewer);
}

void Bullet::setActive(bool a, b2Vec2 pos, b2Vec2 size, b2Vec2 vel, int texture, int damage, int player)
{
	entity_->setActive(a);
	viewer_->setDrawable(a);
	col_->getBody()->SetEnabled(a);

	if (a) { //hacer movidas
		col_->getBody()->SetTransform(pos,0);
		col_->applyLinearImpulse(vel, { 0,0 });
		//SIZE------------
		viewer_->setTexture(texture);
		damage_ = damage;
		player_ = player;
	}
}

void Bullet::onCollisionEnter(Collision* c)
{
	PlayerData* pData = c->entity->getComponent<PlayerData>(ComponentType::PlayerData);
	if (pData != nullptr && pData->getPlayerNumber() != player_) { //solo colisiona con jugadores que no sea el que lo ha lanzado
		std::cout << "aaaaaaaaaaa" << endl;

	}
}
