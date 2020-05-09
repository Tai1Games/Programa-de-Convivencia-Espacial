#include "Viewer.h"
#include "Entity.h"
#include "Resources.h"

Viewer::Viewer() :
	Viewer(Resources::Debug) {	//
}

Viewer::Viewer(int textureId, SDL_Rect clip) :
	Viewer(textureId, clip, ComponentType::Viewer) {	//
}

Viewer::Viewer(int textureId, SDL_Rect clip, ComponentType::CmpId ct) :
	Component(ct), //
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
	if (drawable_) {
		SDL_Rect drawRect = collider_->getRectRender();
		drawRect.x += renderOffset_.x;
		drawRect.y += renderOffset_.y;
		tex_->render(drawRect, collider_->getAngleInDegrees(), clip_); // getAngle devuelve radianes, hay que pasarlos a �ngulos
    }
}

void Viewer::setNFrames(int nFrames) //Es esto feo de cojones y nada intuitivo? Absolutamente. Lo vamos a tirar todo en un futuro para hacer cosas de la UI aparte? También.
{
	nFrames_ = nFrames;
	wH_.x = tex_->getWidth() / nFrames;
}
