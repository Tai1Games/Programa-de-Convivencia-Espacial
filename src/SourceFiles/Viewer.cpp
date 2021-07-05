#include "Viewer.h"
#include "Entity.h"
#include "Resources.h"

Viewer::Viewer() :
	Viewer(Resources::Debug) {	//
}

Viewer::Viewer(int textureId, ComponentType::CmpId ct) :
	Component(ct), //
	transform_(nullptr) {	//
	tex_ = nullptr;
	textureId_ = textureId;
}

Viewer::~Viewer() {
}

void Viewer::init() {
	transform_ = GETCMP1_(Transform);
	AbstractViewers::init();
}

void Viewer::update() {
	if (drawable_) {
		if (transform_ != nullptr) {
			rect = SDL_Rect(transform_->getRectRender());
			rect.x += renderOffset_.x;
			rect.y += renderOffset_.y;
			drawAngle_ = transform_->getAngleInDegrees();
		}
		else std::cout << "No transform!\n";
	}
}

bool operator != (const SDL_Rect& a, const SDL_Rect& b) {
	return a.x != b.x || a.y != b.y || a.w != b.w || a.h != b.h;
}

void Viewer::draw() const
{
	if (drawable_ && rect != comparisonRect) 	{
		tex_->render(rect, drawAngle_, frameX_, frameY_, flip_);
	}
}

Texture* Viewer::setTexture(int text)
{
	std::cout << "Set texture\n";
	textureId_ = text;
	tex_ = SDL_Game::instance()->getTexturesMngr()->getTexture(textureId_);
	return tex_;	
}