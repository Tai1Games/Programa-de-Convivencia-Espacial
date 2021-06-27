#include "AnimatedPlayer.h"

AnimatedPlayer::AnimatedPlayer(int textureId, int timePerFrame, int skin) :
	AdvancedAnimatedViewer(textureId, timePerFrame),
	skin_(skin) {
}

AnimatedPlayer::~AnimatedPlayer()
{
}

void AnimatedPlayer::init()
{
	baseSpeed_ = CONST(int, "PLAYER_TIME_PER_FRAME");
	Viewer::init();

	animationsInfo_ = vector<AnimationInfo>(CONST(int, "NUM_ANIMS"));

	unsigned short int nextAnimOrigin_ = 0;
	int i = 0;
	for (AnimationInfo& a : animationsInfo_) {
		a = {
			nextAnimOrigin_,														// guardamos su origen
			CONST(int, "NFRAMES_ANIM" + std::to_string(i))		//"cargamos" la duraci�n de cada animacion
		};
		nextAnimOrigin_ += a.numFrames_;											//calculamos la posicion de la siguiente animaci�n
		i++;
	}

	frameX_ = animationsInfo_[anim_].animOrigin_;
	frameY_ = skin_;

	hands = GETCMP1_(Hands);
}

void AnimatedPlayer::draw() const 
{
	Viewer::draw();
	

}

void AnimatedPlayer::resetAnimation()
{
	setAnimSpeed(baseSpeed_);
	AdvancedAnimatedViewer::resetAnimation();
}

