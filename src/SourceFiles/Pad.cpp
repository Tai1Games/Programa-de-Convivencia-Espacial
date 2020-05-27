#include "Pad.h"
#include "Collision.h"
#include "Entity.h"
#include "Resources.h"

void Pad::init()
{
	viewer_ = entity_->getComponent<AnimatedViewer>(ComponentType::Viewer); //pilla referencia al viewer
}

void Pad::onCollisionExit(Collision* c)
{
	viewer_->startAnimation(1);
	SDL_Game::instance()->getAudioMngr()->playChannel(Resources::PadSound, 0);
}