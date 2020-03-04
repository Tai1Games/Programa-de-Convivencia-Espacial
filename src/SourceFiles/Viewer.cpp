#include "Viewer.h"
#include "Entity.h"

Viewer::Viewer() : 
	Viewer(Resources::Tinky) {	//
}

Viewer::Viewer(Resources::TextureId tex) :
	Component(ComponentType::Viewer), //
	tex_(nullptr),	//
	collider_(nullptr),
	clip_(SDL_Rect{ 0, 0, 0, 0 }),
	textureId_(tex) {	//
}

Viewer::~Viewer() {

}

void Viewer::init() {
	
	collider_ = GETCMP1_(Collider);
	if (tex_ == nullptr) {
		tex_ = SDL_Game::instance()->getTexturesMngr()->getTexture(textureId_);
		clip_ = SDL_Rect{ 0, 0, tex_->getWidth(), tex_->getHeight() };
	}
}

void Viewer::draw() const {
	tex_->render(collider_->getRect(), collider_->getAngle(), clip_);
}