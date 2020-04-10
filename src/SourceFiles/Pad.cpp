#include "Pad.h"

Pad::Pad() : Component(ComponentType::Pad)
{
}

Pad::~Pad()
{
}

void Pad::init()
{
	onAnimation_ = false;
	frame_ = 0;
	viewer_ = entity_->getComponent<Viewer>(ComponentType::Viewer); //pilla referencia al viewer
}

void Pad::update()
{
	if (onAnimation_) { //se esta moviendo
		int pos = 32 * (frame_ / CONST(int, "PAD_ANIMATION_SPEED"));
		viewer_->setClip(SDL_Rect{ 0, pos ,32,32 });
		frame_++;
		if (frame_ / CONST(int, "PAD_ANIMATION_SPEED") == CONST(int, "PAD_ANIMATION_FRAMES")) { //ha terminado la animacion 
			onAnimation_ = false;
			viewer_->setClip(SDL_Rect{ 0, 0,32,32 });
		}
	}
}

void Pad::startAnim()
{
	frame_ = CONST(int, "PAD_ANIMATION_SPEED"); //empieza en el segundo frame por que el primero es el statico 
	onAnimation_ = true;
}
