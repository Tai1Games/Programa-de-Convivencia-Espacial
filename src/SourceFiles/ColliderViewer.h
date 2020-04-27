#pragma once
#include "Viewer.h"
#include "checkML.h"
#include <vector>

struct DebugColor {
	DebugColor(Uint8 r, Uint8 g, Uint8 b) :
		r(r), g(g), b(b) {
	}
	DebugColor() : DebugColor(255, 255, 255) {};
	Uint8 r = 255, g = 255, b = 255;
};

class ColliderViewer :	public Viewer
{
private:
	DebugColor color;
	SDL_Renderer* renderer_ = nullptr;
	SDL_Point* points_ = nullptr;
	b2Body* body_ = nullptr;
	DebugColor colors[8] = {
		{0, 255, 255},
		{255, 0, 255},
		{255, 255, 0},
		{0, 128, 255},
		{0, 255, 128},
		{255, 0, 128},
		{128, 255, 0},
		{255, 128, 0}
	};

	void drawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius) const;
	void setPoints(b2Fixture* fixture) const;
	void drawRect(b2Fixture* fixture) const;

public:
	ColliderViewer();
	virtual ~ColliderViewer() {
		delete[] points_;
	};
	void init();
	void draw() const;
};
