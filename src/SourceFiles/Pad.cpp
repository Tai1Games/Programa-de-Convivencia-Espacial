#include "Pad.h"
#include "Collision.h"
#include "Entity.h"

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
	animationSpeed_ = CONST(int, "PAD_ANIMATION_SPEED");
	totalFrames_ = CONST(int, "PAD_ANIMATION_FRAMES");
}

void Pad::update()
{
	if (onAnimation_) { //se esta moviendo
		int pos = 32 * (frame_ / animationSpeed_);
		viewer_->setClip(SDL_Rect{ 0, pos ,32,32 });
		frame_++;
		if (frame_ / animationSpeed_ == totalFrames_) { //ha terminado la animacion 
			onAnimation_ = false;
			viewer_->setClip(SDL_Rect{ 0, 0,32,32 });
		}
	}
}

void Pad::startAnim()
{
	frame_ = animationSpeed_; //empieza en el segundo frame por que el primero es el statico 
	onAnimation_ = true;
}

void Pad::onCollisionEnter(Collision* c) {
	if (c->entity->hasComponent(ComponentType::PlayerController)) {
		cout << "HAHA player go boink" << endl;
	}
}

void Pad::onCollisionExit(Collision* c)
{
	startAnim();
}
