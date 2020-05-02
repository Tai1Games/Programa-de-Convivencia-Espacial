#include "Bullet.h"

void Bullet::init()
{
	winWidth_ = CONST(int, "WINDOW_WIDTH");
	winHeight_ = CONST(int, "WINDOW_HEIGHT");
	col_ = GETCMP1_(Collider);
	viewer_ = GETCMP1_(Viewer);
}

void Bullet::update()
{
	if (col_->getPos().x < 0 || col_->getPos().y > winWidth_ || //se elimina si se sale de la pantalla
		col_->getPos().y < 0 || col_->getPos().y > winHeight_) needToDelete = true;

	if (needToDelete) {
		setActive(false);
		needToDelete = false;
	}
}

void Bullet::setActive(bool a, b2Vec2 pos, b2Vec2 size, b2Vec2 vel, int texture, int damage, int player)
{
	entity_->setActive(a);
	viewer_->setDrawable(a);
	col_->getBody()->SetEnabled(a);

	if (a) { //hacer movidas
		col_->getBody()->SetTransform(pos, 0);
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
		Health* pHealth_ = c->entity->getComponent<Health>(ComponentType::Health);
		if (pHealth_ != nullptr) {
			if (!pHealth_->subtractLife(damage_)) {
				pHealth_->playerDead(c->collisionHandler);
				needToDelete = true;
			}
		}
		else {
			Wallet* wallet = GETCMP2(c->entity, Wallet);
			if (wallet != nullptr) {
				c->collisionHandler->addCoinDrop(std::make_tuple(wallet, pData, CONST(int, "BANANA_BULLET_COIN_DMG")));
				needToDelete = true;
			}
		}
	}
}
