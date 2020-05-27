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

	const static int numlayers = 12;
	// SE PUEDEN CAMBIAR ESTOS COLORES COMO QUER�IS
	DebugColor colors[numlayers] = {
		{0, 255, 255},		// NormalObject
		{255, 0, 255},		// NormalAttachableObject
		{255, 255, 0},		// UnInteractableObject
		{255, 0, 0},		// Wall
		{0, 255, 0},		// Trigger
		{0, 0, 255},		// PickableObject
		{128, 255, 0},		// NonGrababbleWall
		{255, 128, 0},		// Player1
		{255, 0, 128},		// Player2
		{0, 255, 128},		// Player3
		{255, 255, 255},	// Player4
		{0, 0, 0}			// NULL
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
