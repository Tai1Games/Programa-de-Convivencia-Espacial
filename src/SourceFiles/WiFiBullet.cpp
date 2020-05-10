#include "WiFiBullet.h"
#include "Collider.h"

void WiFiBullet::onCollisionEnter(Collision* c)
{
	PlayerData* pData = c->entity->getComponent<PlayerData>(ComponentType::PlayerData);
	if (pData != nullptr && pData->getPlayerNumber() == player_) { //solo colisiona con el jugador objetivo
		needToDelete = true;
	}
}

void WiFiBullet::onCollisionExit(Collision* c) {
	Entity* cEntity = c->entity;
	Collider* cCollider = GETCMP2(cEntity, Collider);

	if (routerCollider_ != nullptr && cCollider != nullptr &&
		routerCollider_ == cCollider) {
		needToDelete = true;
	}
}
