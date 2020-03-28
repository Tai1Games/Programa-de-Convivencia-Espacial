#include "RouterLogic.h"
#include "Entity.h"
#include "WiFightGameMode.h"

void RouterLogic::detectPlayer(Collider* playerDetected, int id)
{
	PlayerInfo newPlayer;
	newPlayer.posPlayer = playerDetected;
	newPlayer.id = id;
	playersInsideRange_.push_back(newPlayer);
}

void RouterLogic::loseContactPlayer(Collider* playerDetected, int id) {
	vector<PlayerInfo>::iterator it = playersInsideRange_.begin();
	while (it->id != id && it->posPlayer != playerDetected && it != playersInsideRange_.end()) {
		++it;
	}
	if (it != playersInsideRange_.end()) playersInsideRange_.erase(it);
}

void RouterLogic::init()
{
	posRouter_ = GETCMP1_(Collider);
}

void RouterLogic::update()
{	//5 should be a constant and points should be based on distance from the router and number of players in the area. More players inside = less points for everyone else.
	for (int k = 0; k < playersInsideRange_.size(); k++) {
		wifightGameMode_->addPoints(playersInsideRange_[k].id, 5); 
	}
}
