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

Viewer::Viewer(int textureId, SDL_Rect clip) :
	Component(ComponentType::Viewer), //
	tex_(nullptr),	//
	collider_(nullptr),
	clip_(clip),
	textureId_(textureId) {	//
}

Viewer::Viewer(int textureId, b2Vec2 pos, float scale, float angle, const SDL_RendererFlip& flip) :
	Component(ComponentType::Viewer),
	tex_(nullptr),	//
	collider_(nullptr),
	pos_(b2Vec2(pos)),
	clip_(SDL_Rect{ 0, 0, 0, 0 }),
	textureId_(textureId),
	isUIElement_(true),
	scale_(scale), //
	angle_(angle),
	flip_(flip)
{
}

Viewer::Viewer(int textureId, b2Vec2 pos, float scale, float angle, SDL_Rect clip) :
	Component(ComponentType::Viewer),
	tex_(nullptr),	//
	collider_(nullptr),
	pos_(b2Vec2(pos)),
	clip_(clip),
	textureId_(textureId),
	isUIElement_(true),
	scale_(scale), //
	angle_(angle)
{
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
	wH_ = b2Vec2(tex_->getWidth(), tex_->getHeight());
}
void Viewer::draw() const {
	if (drawable_) {
		if (!isUIElement_) {
			SDL_Rect drawRect = collider_->getRectRender();
			drawRect.x += renderOffset_.x;
			drawRect.y += renderOffset_.y;
			tex_->render(drawRect, collider_->getAngleInDegrees(), clip_); // getAngle devuelve radianes, hay que pasarlos a �ngulos
			//if (textureId_ == Resources::Fireball) {
			//	cout << "BOLADEFUEGODIBUJANDOSE";
			//}
		}
		else {
			SDL_Rect dest;
			dest.x = pos_.x + renderOffset_.x;
			dest.y = pos_.y + renderOffset_.y;
			dest.w = wH_.x * scale_;
			dest.h = wH_.y * scale_;
			tex_->render(dest, angle_, clip_, flip_);

		}
	}
}
