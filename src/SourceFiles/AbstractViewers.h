#pragma once
#include <SDL_rect.h>
#include <SDL.h>
#include <b2_math.h>

class Texture;
class AbstractViewers
{
protected:
	int textureId_;
	int nFrames_ = 1;
	Texture* tex_;
	bool drawable_ = true;
	b2Vec2 renderOffset_ = b2Vec2(0, 0);
	b2Vec2 wH_;
	unsigned short int frameX_ = 0, frameY_ = 0;
	SDL_RendererFlip flip_ = SDL_FLIP_NONE;
public:
	void init();

	void setNFrames(int nFrames);
	virtual void setDrawable(bool b) { drawable_ = b; }
	void setOffset(b2Vec2 newOffset) { renderOffset_ = newOffset; }

	int getTextureId() { return textureId_; }
	Texture* getTexture() { return tex_; }

	void setFrame(unsigned short frameX, unsigned short frameY = 0) {
		frameX_ = frameX;
		frameY_ = frameY;
	};

	unsigned short int getFrameX() const {
		return frameX_;
	};
	unsigned short int getFrameY() const {
		return frameY_;
	};
};

