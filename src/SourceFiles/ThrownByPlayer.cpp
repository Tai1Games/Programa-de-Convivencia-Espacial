#include "ThrownByPlayer.h"
#include "Collision.h"

void ThrownByPlayer::init() {
	timeToDeleteOwner_ = CONST(double, "TIME_TO_UNLINK_OBJECT_FROM_PLAYER");
	sPerFrame_ = CONST(double, "SECONDS_PER_FRAME");
}

void ThrownByPlayer::update()
{
	if (lastOwner_ != -1) {
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

void ThrownByPlayer::onCollisionExit(Collision* c)
{
	Health* h = nullptr;
	if (lastOwner_ != -1 && (h = GETCMP_FROM_FIXTURE_(c->hitFixture, Health))) {
		if (h->getHealth() <= 0) {
			cout << "PLAYER MUERTO" << endl;
		}
	}
}

void ThrownByPlayer::addPointsToOwner()
{
	gameMode_->addPoints(lastOwner_);
}
