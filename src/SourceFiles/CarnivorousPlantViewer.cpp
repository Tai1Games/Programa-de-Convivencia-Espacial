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
	if (isPlaying_ && anim_ != -1 && updateTime(animationsInfo_[anim_].numFrames_)) {

		// deja pasar framesUntilReopenMouth_ frames para volver a abrir la boca
		if (!isPlaying_) {
			frameCounter_++;
			if (frameCounter_ >= framesUntilReopenMouth_) {
				resumeAnimation();
				frameCounter_ = 0;
				opening_ = true;
			}
		}
		// vuelve a la normalidad tras morder
		else if (opening_) {
			frameCounter_++;
			if (frameCounter_ == animationsInfo_[1].numFrames_) {
				anim_ = 0;
				opening_ = false;
				frameCounter_ = 0;
			}
		}

		frameX_ = animationsInfo_[anim_].animOrigin_ + frame_;
		if (loops_ != -1 && currentLoop_ >= loops_ && (anim_ == 1 && frame_ == frameClosedMouth_)) {	// para saber si hay que volver al idle
			resetAnimation();
		}
	}
}


void CarnivorousPlantViewer::resetAnimation()
{
	setAnimSpeed(minFramesSpeed_);
	pauseAnimation();
}
