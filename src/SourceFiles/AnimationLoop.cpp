#include "AnimationLoop.h"

void AnimationLoop::init()
{
	image = GETCMP1_(Viewer);
	start = SDL_GetTicks();
}

void AnimationLoop::update()
{
	if(start + speed < SDL_GetTicks()){
		start = SDL_GetTicks();

		frame = frame % nframes;
		image->setClip(SDL_Rect{ (clip.w * frame), 0, clip.w, clip.h});
		frame++;
	}
}


