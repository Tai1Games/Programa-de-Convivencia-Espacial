#pragma once
#include "Component.h"
#include "Vector2D.h"
#include "checkML.h"
#include "box2d.h"


class Transform : public Component
{
public:
	Transform(Vector2D pos, double rot, double w, double h) : Component(ComponentType::Transform) {
		position_ = pos; rotation_ = rot; width_ = w, heigth_ = h;
	};
	Transform(b2Body* b) : Component(ComponentType::Transform){
		body_ = b; position_ = Vector2D(0,0); rotation_ = 0; width_ = 200, heigth_ = 200;
	}
	virtual ~Transform() {};

	//posición
	const Vector2D& getPos() const { return Vector2D((double)body_->GetPosition().x,-(double)body_->GetPosition().y); }
	double getPosX() { return (double)body_->GetPosition().x; }
	double getPosY() { return -(double)body_->GetPosition().y; }

	void setPos(Vector2D vec) { body_->SetTransform(b2Vec2(vec.getX(),-vec.getY()),body_->GetAngle()); }
	void setPos(double x, double y) { body_->SetTransform(b2Vec2(x, -y), body_->GetAngle()); }
	void setPosX(double x) { body_->SetTransform(b2Vec2(x,body_->GetPosition().y),body_->GetAngle()); }
	void setPosY(double y) {  body_->SetTransform(b2Vec2(body_->GetPosition().x,-y),body_->GetAngle());  }

	//rotación
	double getRot() { return (double)body_->GetAngle(); }
	void setRot(int rot) { body_->SetTransform(b2Vec2(body_->GetPosition().x, body_->GetPosition().y), rot); }

	//width, heigth
	double getW() { return width_; }
	double getH() { return heigth_; }
	void setWH(double w, double h) { width_ = w; heigth_ = h; }
	void setW(double w) { width_ = w; }
	void setH(double h) { heigth_ = h; }

	b2Body* getBody() { return body_; }

	//destRect
	SDL_Rect getDestRect() const {
		SDL_Rect r;

		r.x = body_->GetPosition().x;
		r.y = -body_->GetPosition().y;
		r.w = width_;
		r.h = heigth_;

		return r;
	}

private:
	b2Body* body_;
	Vector2D position_;
	double rotation_;
	double width_;
	double heigth_;
};

