#include "AbstractViewers.h"
#include "Texture.h"
#include "SDL_Game.h"

void AbstractViewers::init()
{
	if (tex_ == nullptr)
		tex_ = SDL_Game::instance()->getTexturesMngr()->getTexture(textureId_);
	wH_ = b2Vec2(tex_->getFrameWidth(), tex_->getFrameHeight());
}

void AbstractViewers::setNFrames(int nFrames)
{
	nFrames_ = nFrames;
	wH_.x = tex_->getWidth() / nFrames;
}
