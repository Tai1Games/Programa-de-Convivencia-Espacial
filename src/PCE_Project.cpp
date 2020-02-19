#include "SDL.h"
#include "box2d.h"

int main(int argc, char* argv[]) {
	SDL_Rect a;
	b2Vec2 gravity(0, -9.8);
	b2World world(gravity);
	return 0;
}