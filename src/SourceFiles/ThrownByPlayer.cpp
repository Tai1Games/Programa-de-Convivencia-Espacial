#include "ThrownByPlayer.h"
#include "Collision.h"

void ThrownByPlayer::init() {
	timeToDeleteOwner_ = CONST(double, "TIME_TO_UNLINK_OBJECT_FROM_PLAYER");
	sPerFrame_ = CONST(double, "SECONDS_PER_FRAME");
}

void ThrownByPlayer::update()
{
	if (lastOwner_ != -1 && timeWhenThrown_ != -1) {
		timeWhenThrown_ += sPerFrame_;
		if (timeWhenThrown_ > timeToDeleteOwner_) {
			lastOwner_ = -1;
		}
	}
}

void ThrownByPlayer::throwObject(int playerId)
{
	timeWhenThrown_ = 0;
	lastOwner_ = playerId;
}

void ThrownByPlayer::addPointsToOwner()
{
	if (lastOwner_ != -1)
		gameMode_->playerKillsPlayer(lastOwner_);
}

void ThrownByPlayer::SetOwner(int playerId) {
	lastOwner_ = playerId;
	timeWhenThrown_ = -1;
}
