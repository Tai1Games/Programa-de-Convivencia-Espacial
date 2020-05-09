#include "UIViewer.h"

UIViewer::UIViewer(int textureId, b2Vec2 pos, float scale, float angle, SDL_Rect clip, const SDL_RendererFlip& flip) :
	Component(ComponentType::Viewer),
	tex_(nullptr),	//
	pos_(b2Vec2(pos)),
	clip_(clip),
	textureId_(textureId),
	scale_(scale), //
	angle_(angle),
	flip_(flip)
{
}

UIViewer::~UIViewer()
{
}

void UIViewer::init()
{
	if (tex_ == nullptr) {
		tex_ = SDL_Game::instance()->getTexturesMngr()->getTexture(textureId_);
		if (clip_.w == 0 && clip_.h == 0)
			clip_ = SDL_Rect{ 0, 0, tex_->getWidth(), tex_->getHeight() };
	}
	wH_ = b2Vec2(tex_->getWidth(), tex_->getHeight());
}

void UIViewer::draw() const
{
	if (drawable_) {
		SDL_Rect dest;
		dest.x = pos_.x + renderOffset_.x;
		dest.y = pos_.y + renderOffset_.y;
		dest.w = wH_.x * scale_;
		dest.h = wH_.y * scale_;
		tex_->render(dest, angle_, clip_, flip_);
	}
}

void UIViewer::setNFrames(int nFrames)
{
	nFrames_ = nFrames;
	wH_.x = tex_->getWidth() / nFrames;
}
