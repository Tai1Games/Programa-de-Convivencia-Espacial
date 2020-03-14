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

Viewer::~Viewer() {

}

void Viewer::init() {
	
	collider_ = GETCMP1_(Collider);
	if (tex_ == nullptr) {
		tex_ = SDL_Game::instance()->getTexturesMngr()->getTexture(textureId_);
		if(clip_.w == 0 && clip_.h == 0)
			clip_ = SDL_Rect{ 0, 0, tex_->getWidth(), tex_->getHeight() };
	}
}

void Viewer::draw() const {
	tex_->render(collider_->getRectRender(), (collider_->getAngle()*-180/PI ), clip_); // getAngle devuelve radianes, hay que pasarlos a ángulos
}