#include "Viewer.h"
#include "Entity.h"
#include "Resources.h"

Viewer::Viewer() :
	Viewer(Resources::Debug) {	//
}

Viewer::Viewer(int textureId, SDL_Rect clip, ComponentType::CmpId ct) :
	Component(ct), //
	collider_(nullptr){	//
	tex_ = nullptr;
	clip_ = clip;
	textureId_ = textureId;
}

Viewer::~Viewer() {
}

void Viewer::init() {
	collider_ = GETCMP1_(Collider);
	AbstractViewers::init();
}
void Viewer::draw() const {
	if (drawable_) {
		SDL_Rect drawRect = collider_->getRectRender();
		drawRect.x += renderOffset_.x;
		drawRect.y += renderOffset_.y;
		tex_->render(drawRect, collider_->getAngleInDegrees(), clip_); // getAngle devuelve radianes, hay que pasarlos a �ngulos
    }
}

