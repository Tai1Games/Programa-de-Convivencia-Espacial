#pragma once
#include <SDL_rect.h>
#include <b2_math.h>

class Texture;
class AbstractViewers
{
protected:
	int textureId_;
	int nFrames_ = 1;
	Texture* tex_;
	SDL_Rect clip_;
	bool drawable_ = true;
	b2Vec2 renderOffset_ = b2Vec2(0, 0);
	b2Vec2 wH_;
	unsigned short int frameX_ = 0, frameY_ = 0;
public:
	void init();

	void setNFrames(int nFrames);
	void setDrawable(bool b) { drawable_ = b; }
	void setClip(SDL_Rect clip) { clip_ = clip; }
	void setOffset(b2Vec2 newOffset) { renderOffset_ = newOffset; }

	int getTextureId() { return textureId_; }
	Texture* getTexture() { return tex_; }
};

