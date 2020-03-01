#include "Viewer.h"

Viewer::Viewer():
	Component(ComponentType::Viewer), //
	tex_(nullptr),	//
	tr_(nullptr) {	//
}

Viewer::~Viewer() {

}

void Viewer::init() {
	
	tr_ = GETCMP1_(Transform);
	tex_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Tinky);
}

void Viewer::draw() const {
	tex_->render(tr_->getDestRect(), tr_->getRot());
}