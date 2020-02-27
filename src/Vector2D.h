#pragma once

#include <iostream>
#include <math.h>

using namespace std;

class Vector2D {
	double x_;  // first coordinate
	double y_;  // second coordinate
public:
	Vector2D();
	Vector2D(const Vector2D& v);
	Vector2D(double x, double y);
	virtual ~Vector2D();

	inline double getX() const {
		return x_;
	}
	inline double getY() const {
		return y_;
	}
	inline void setX(double x) {
		x_ = x;
	}
	inline void setY(double y) {
		y_ = y;
	}
	inline void set(const Vector2D& v) {
		x_ = v.x_;
		y_ = v.y_;
	}
	inline void set(double x, double y) {
		x_ = x;
		y_ = y;
	}
	inline double magnitude() const {
		return sqrt(pow(x_, 2) + pow(y_, 2));
	}

	Vector2D rotate(double degrees) const;
	double angle(const Vector2D& v) const;
	Vector2D normalize() const;

	inline Vector2D operator-(const Vector2D& v) const {
		return Vector2D(x_ - v.x_, y_ - v.y_);
	}

	inline Vector2D operator+(const Vector2D& v) const {
		return Vector2D(x_ + v.x_, y_ + v.y_);
	}
	inline Vector2D operator*(double d) const {
		return Vector2D(x_ * d, y_ * d);
	}
	inline double operator *(const Vector2D& d) const {
		return d.x_ * x_ + d.y_ * y_;
	}
	Vector2D operator/(double d) const {
		return Vector2D(x_ / d, y_ / d);
	}
	friend ostream& operator<<(ostream& os, const Vector2D& v);
};
