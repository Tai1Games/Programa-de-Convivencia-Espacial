#pragma once
#include "Component.h"
#include "Vector2D.h"
#include "checkML.h"


class Transform : public Component
{
public:
	Transform(Vector2D pos, double rot, double w, double h) : Component(ComponentType::Transform) {
		position_ = pos; rotation_ = rot; width_ = w, heigth_ = h;
	};
	virtual ~Transform() {};

	//posición
	const Vector2D& getPos() const { return position_; }
	double getPosX() { return position_.getX(); }
	double getPosY() { return position_.getY(); }

	void setPos(Vector2D vec) { position_ = vec; }
	void setPos(double x, double y) { position_.set(x, y); }
	void setPosX(double x) { position_.setX(x); }
	void setPosY(double y) { position_.setY(y); }

	//rotación
	double getRot() { return rotation_; }
	void setRot(int rot) { rotation_ = rot; }

	//width, heigth
	double getW() { return width_; }
	double getH() { return heigth_; }
	void setWH(double w, double h) { width_ = w; heigth_ = h; }
	void setW(double w) { width_ = w; }
	void setH(double h) { heigth_ = h; }

	//destRect
	SDL_Rect getDestRect() const {
		SDL_Rect r;

		r.x = position_.getX();
		r.y = position_.getY();
		r.w = width_;
		r.h = heigth_;

		return r;
	}

private:
	Vector2D position_;
	double rotation_;
	double width_;
	double heigth_;
};

