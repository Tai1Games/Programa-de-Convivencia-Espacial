#include "AnimatedPlayer.h"

AnimatedPlayer::AnimatedPlayer(int textureId, int skin) : Viewer(textureId, ComponentType::AnimatedPlayer) {
	animationsInfo_ = vector<AnimationInfo>( CONST(int, "NUM_ANIMS"));
	skin_ = skin;	
}

AnimatedPlayer::~AnimatedPlayer()
{
}

void AnimatedPlayer::init()
{
	Viewer::init(); 

	unsigned short int nextAnimOrigin_ = 0;
	int i = 0;
	for (AnimationInfo& a : animationsInfo_) {
		a = {
			nextAnimOrigin_,														// guardamos su origen
			(unsigned short int)CONST(int, "NFRAMES_ANIM" + std::to_string(i))		//"cargamos" la duración de cada animacion
		};
		nextAnimOrigin_ += a.numFrames_;											//calculamos la posicion de la siguiente animación
		i++;
	}

	//fWidth_ = tex_->getWidth() / nextAnimOrigin_;
	//fHeight_ = tex_->getHeight() / CONST(int, "NUM_SKINS");

	frameX_ = animationsInfo_[anim_].animOrigin_;
	frameY_ = skin_;
	//setClip(SDL_Rect{ cumFrameData_[anim_] + frame_ * fWidth_, skin_ * fHeight_,  fWidth_, fHeight_ });
}

void AnimatedPlayer::update()
{
	if (anim_ != -1 && isPlaying_ && updateTime(animationsInfo_[anim_].numFrames_)) {
		frameX_ = animationsInfo_[anim_].animOrigin_ + frame_;
		if (!isLooping_ && currentLoop_ > maxLoops_) {
			anim_ = -1;
			currentLoop_ = 0;
		}
	}
}

void AnimatedPlayer::play()
{
	isPlaying_ = true;
}

void AnimatedPlayer::pause()
{
	isPlaying_ = false;
}

void AnimatedPlayer::stop()
{
	isPlaying_ = false;
	anim_ = -1;
	frame_ = -1;
}
