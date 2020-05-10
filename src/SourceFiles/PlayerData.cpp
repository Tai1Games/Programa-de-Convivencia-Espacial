#include "PlayerData.h"
#include "Entity.h"

void PlayerData::init() {
	ib->setPlayerCol(GETCMP1_(Collider));
}