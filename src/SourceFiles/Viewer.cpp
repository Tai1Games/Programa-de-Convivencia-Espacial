#include "Viewer.h"
#include "Entity.h"
#include "Resources.h"

Viewer::Viewer() :
	Viewer(Resources::Debug) {	//
}

Viewer::Viewer(int textureId) :
	Component(ComponentType::Viewer), //
	tex_(nullptr),	//
	collider_(nullptr),
	clip_(SDL_Rect{ 0, 0, 0, 0 }),
	textureId_(textureId) {	//
}

Viewer::Viewer(int textureId, float x, float y, float scale) :
	Component(ComponentType::Viewer),
	tex_(nullptr),	//
	collider_(nullptr),
	pos_(b2Vec2(x,y)),
	textureId_(textureId),
	isUIElement_(true),
    scale_(scale)//
{
}

Viewer::Viewer(int textureId, SDL_Rect clip) :
	Component(ComponentType::Viewer), //
	tex_(nullptr),	//
	collider_(nullptr),
	clip_(clip),
	textureId_(textureId) {	//
}

Viewer::~Viewer() {

}

void Viewer::init() {

	if(!isUIElement_) collider_ = GETCMP1_(Collider);
	if (tex_ == nullptr) {
		tex_ = SDL_Game::instance()->getTexturesMngr()->getTexture(textureId_);
		if(clip_.w == 0 && clip_.h == 0)
			clip_ = SDL_Rect{ 0, 0, tex_->getWidth(), tex_->getHeight() };
	}
}

void Viewer::draw() const {
	if (drawable_) {
		if (!isUIElement_) tex_->render(collider_->getRectRender(), (collider_->getAngle() * -180 / PI), clip_); // getAngle devuelve radianes, hay que pasarlos a �ngulos
		else {
			SDL_Rect dest;
			dest.x = pos_.x;
			dest.y = pos_.y;
			dest.w = tex_->getWidth() * scale_;
			dest.h = tex_->getHeight() * scale_;
			tex_->render(dest);
		}
	}
}
