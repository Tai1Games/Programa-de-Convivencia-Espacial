#include "AbstractViewers.h"
#include "Texture.h"
#include "SDL_Game.h"

void AbstractViewers::init()
{
	if (tex_ == nullptr) {
		tex_ = SDL_Game::instance()->getTexturesMngr()->getTexture(textureId_);
		if (clip_.w == 0 && clip_.h == 0)
			clip_ = SDL_Rect{ 0, 0, tex_->getWidth(), tex_->getHeight() };
	}
	wH_ = b2Vec2(tex_->getWidth(), tex_->getHeight());
}

void AbstractViewers::setNFrames(int nFrames)
{
	nFrames_ = nFrames;
	wH_.x = tex_->getWidth() / nFrames;
}
