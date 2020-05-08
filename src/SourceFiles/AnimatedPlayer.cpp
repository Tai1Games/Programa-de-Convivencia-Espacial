#include "AnimatedPlayer.h"

AnimatedPlayer::AnimatedPlayer(int textureId, int skin) : Viewer(textureId, SDL_Rect(), ComponentType::AnimatedPlayer) {
	frameData_= vector<int>( CONST(int, "NUM_ANIMS"));
	cumFrameData_= vector<int>(frameData_.size());
	skin_ = skin;	
}

AnimatedPlayer::~AnimatedPlayer()
{
}

void AnimatedPlayer::init()
{
	Viewer::init(); 

	string name;
	for (int i = 0; i < frameData_.size(); i++) {
		string name = "NFRAMES_ANIM" + std::to_string(i);
		frameData_[i] = (CONST(int, name));	//"cargamos" la duración de cada animacion
		cumFrameData_[i] = (numFrames_);				//cada valor del acumulado es igual a la suma de elementos anteriores 
		numFrames_ += frameData_[i];					//calculamos la suma del total
	}

	fWidth_ = tex_->getWidth() / numFrames_;
	fHeight_ = tex_->getHeight() / CONST(int, "NUM_SKINS");

	setClip(SDL_Rect{ cumFrameData_[anim_] + frame_ * fWidth_, skin_ * fHeight_,  fWidth_, fHeight_ });
}

void AnimatedPlayer::update()
{
	if (anim_ != -1 && isPlaying_) {

		timeElapsed_++;

		if (timeElapsed_ == timePerFrame_) {
			timeElapsed_ = 0;

			frame_++;

			setClip(SDL_Rect{ cumFrameData_[anim_] * fWidth_ + frame_ * fWidth_, skin_ * fHeight_,  fWidth_, fHeight_ });

			if (frame_ == frameData_[anim_]) {	//si es el ultimo frame, reseteamos
				
				if (isLooping_) {
					setClip(SDL_Rect{ 0, skin_ * fHeight_,  fWidth_, fHeight_ });
					frame_ = 0;
				} else {
					setClip(SDL_Rect{ 0, skin_ * fHeight_,  fWidth_, fHeight_ });
					frame_ = 0;
					anim_ = -1;
				}

			};
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
