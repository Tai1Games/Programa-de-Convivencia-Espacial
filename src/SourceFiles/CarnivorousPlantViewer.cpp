#include "CarnivorousPlantViewer.h"

CarnivorousPlantViewer::CarnivorousPlantViewer(int textureId, int timePerFrame) :
	AdvancedAnimatedViewer(textureId, timePerFrame),
	minFramesSpeed_(timePerFrame) { 
}

CarnivorousPlantViewer::~CarnivorousPlantViewer()
{
}

void CarnivorousPlantViewer::init()
{
	Viewer::init();

	animationsInfo_ = vector<AnimationInfo>(CONST(int, "CARNIVOROUSPLANT_ANIMATIONS"));
	framesUntilReopenMouth_ = CONST(int, "CARNIVOROUSPLANT_FRAMES_UNITL_REOPEN");
	frameClosedMouth_ = CONST(int, "CARNIVOROUSPLANT_FRAME_CLOSED_MOUTH");

	unsigned short int nextAnimOrigin_ = 0;
	int i = 0;
	for (AnimationInfo& a : animationsInfo_) {
		a = {
			nextAnimOrigin_,																				// guardamos su origen
			CONST(int, "CARNIVOROUSPLANT_NFRAMES_ANIM" + std::to_string(i))		//"cargamos" la duración de cada animacion
		};
		nextAnimOrigin_ += a.numFrames_;																	//calculamos la posicion de la siguiente animación
		i++;
	}

	frameX_ = animationsInfo_[anim_].animOrigin_;
}

void CarnivorousPlantViewer::update()
{
<<<<<<< HEAD
	if (!isPlaying_) {
		frameCounter_++;
		if (frameCounter_ >= framesUntilReopenMouth_) {
			frameCounter_ = 0;
			resumeAnimation();
		}
	}
=======
>>>>>>> master
	if (isPlaying_ && anim_ != -1 && updateTime(animationsInfo_[anim_].numFrames_)) {
		frameX_ = animationsInfo_[anim_].animOrigin_ + frame_;
		if (loops_ != -1 && currentLoop_ >= loops_) {	// para saber si hay que volver al idle
			if (anim_ == 1) {
<<<<<<< HEAD
				if (frame_ == frameClosedMouth_) {
					pauseAnimation();
				}
				else if(frame_ == animationsInfo_[anim_].numFrames_ - 1){
					resetAnimation();
					setAnimSpeed(minFramesSpeed_);
=======
				if (frameX_ == frameClosedMouth_ + animationsInfo_[anim_].animOrigin_) {
					setAnimSpeed(minFramesSpeed_ * framesUntilReopenMouth_);
				}
				else if (frameX_ == frameClosedMouth_ + 1 + animationsInfo_[anim_].animOrigin_) {
					setAnimSpeed(minFramesSpeed_);
				}
				else if(frame_ == animationsInfo_[anim_].numFrames_ - 1){
					resetAnimation();
>>>>>>> master
				}
			}
		}
	}
}