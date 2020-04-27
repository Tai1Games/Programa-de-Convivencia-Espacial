#pragma once
#include "Viewer.h"
#include "checkML.h"

class ColliderViewer :	public Viewer
{
private:
	Uint8 r_ = 255, g_ = 255, b_ = 255, alpha_ = 255;
	SDL_Renderer* renderer_ = nullptr;
	SDL_Point* points_ = nullptr;
	b2Body* body_ = nullptr;

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

