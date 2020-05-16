#pragma once
#include "Viewer.h"
#include "checkML.h"
#include "Collider.h"

struct DebugColor {
	DebugColor(Uint8 r, Uint8 g, Uint8 b) :
		r(r), g(g), b(b) {
	}
	DebugColor() : DebugColor(255, 255, 255) {};
	Uint8 r = 255, g = 255, b = 255;
};

class ColliderViewer : public Viewer
{
private:
	SDL_Renderer* renderer_ = nullptr;
	SDL_Point* points_ = nullptr;
	b2Body* body_ = nullptr;
	Collider* collider_ = nullptr;

	// SE PUEDEN CAMBIAR ESTOS COLORES COMO QUER�IS
	DebugColor colors[9] = {
		{0, 255, 255},
		{255, 0, 255},
		{255, 255, 0},
		{255, 0, 0},
		{0, 255, 0},
		{0, 0, 255},
		{128, 255, 0},
		{255, 255, 255},
		{0, 0, 0}
	};
	double PIXELS_PER_METER = 1.0;

	void drawCircle(SDL_Rect* rect) const;
	void setPoints(double originX, double originY, double width, double height) const;
	void drawRect(SDL_Rect* rect) const;

public:
	ColliderViewer();
	virtual ~ColliderViewer() {
		delete[] points_;
	};
	void init();
	void draw() const;
};
