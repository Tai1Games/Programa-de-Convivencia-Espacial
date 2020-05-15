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
	viewer_ = entity_->getComponent<AnimatedViewer>(ComponentType::Viewer); //pilla referencia al viewer
}

void Pad::onCollisionExit(Collision* c)
{
	viewer_->startAnimation(1);
}
