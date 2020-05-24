#include "Viewer.h"
#include "Entity.h"
#include "Resources.h"

Viewer::Viewer() :
	Viewer(Resources::Debug) {	//
}

Viewer::Viewer(int textureId, ComponentType::CmpId ct) :
	Component(ct), //
	transform_(nullptr){	//
	tex_ = nullptr;
	textureId_ = textureId;
}

Viewer::~Viewer() {
}

void Viewer::init() {
	transform_ = GETCMP1_(Transform);
	AbstractViewers::init();
}
void Viewer::draw() const {
	if (drawable_) {
		SDL_Rect drawRect = transform_->getRectRender();
		drawRect.x += renderOffset_.x;
		drawRect.y += renderOffset_.y;
		tex_->render(drawRect, transform_->getAngleInDegrees(), frameX_, frameY_, flip_); // getAngle devuelve radianes, hay que pasarlos a �ngulos
    }
}
