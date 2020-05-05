#include "UIViewer.h"

UIViewer::UIViewer(int textureId, b2Vec2 pos, float scale, float angle, const SDL_RendererFlip& flip) :
	Component(ComponentType::Viewer),
	tex_(nullptr),	//
	pos_(b2Vec2(pos)),
	clip_(SDL_Rect{ 0, 0, 0, 0 }),
	textureId_(textureId),
	isUIElement_(true),
	scale_(scale), //
	angle_(angle),
	flip_(flip)
{
}

UIViewer::UIViewer(int textureId, b2Vec2 pos, float scale, float angle, SDL_Rect clip) :
	Component(ComponentType::Viewer),
	tex_(nullptr),	//
	pos_(b2Vec2(pos)),
	clip_(clip),
	textureId_(textureId),
	isUIElement_(true),
	scale_(scale), //
	angle_(angle)
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
	SDL_Rect dest;
	dest.x = pos_.x;
	dest.y = pos_.y;
	dest.w = wH_.x * scale_;
	dest.h = wH_.y * scale_;
	tex_->render(dest, angle_, clip_, flip_);
}
