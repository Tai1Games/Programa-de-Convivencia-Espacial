#include "Viewer.h"
#include "Entity.h"
#include "Resources.h"

Viewer::Viewer():
	Component(ComponentType::Viewer), //
	tex_(nullptr),	//
	collider_(nullptr) {	//
}

Viewer::~Viewer() {

}

void Viewer::init() {
	
	collider_ = GETCMP1_(Collider);
	tex_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Tinky);
}

void Viewer::draw() const {

	SDL_Rect rect {
		collider_->getPos().x, collider_->getPos().y,
		collider_->getW(), collider_->getH()
	};

	tex_->render(rect, collider_->getAngle());
}