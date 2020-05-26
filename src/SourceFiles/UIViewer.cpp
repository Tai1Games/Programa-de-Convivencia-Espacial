#include "UIViewer.h"

UIViewer::UIViewer(int textureId, b2Vec2 pos, float scale, float angle, const SDL_RendererFlip& flip, ComponentType::CmpId ct) :
	Component(ct),
	pos_(b2Vec2(pos)),
	scale_(scale), //
	angle_(angle),
	flip_(flip)
{
	tex_ = nullptr;
	textureId_ = textureId;
}

UIViewer::~UIViewer()
{
}

void UIViewer::init()
{
	AbstractViewers::init();
}

void UIViewer::draw() const
{
	if (drawable_) {
		SDL_Rect dest;
		dest.x = pos_.x + renderOffset_.x;
		dest.y = pos_.y + renderOffset_.y;
		dest.w = wH_.x * scale_;
		dest.h = wH_.y * scale_;
		tex_->render(dest, angle_, frameX_, frameY_, flip_);
	}
}

int UIViewer::getW()
{
	if (tex_ == nullptr)	return 0;
	else return tex_->getWidth();
}

int UIViewer::getH()
{
	if (tex_ == nullptr)	return 0;
	else return tex_->getHeight();
}
