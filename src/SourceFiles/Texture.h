#pragma once

#include <SDL.h>
#include "Font.h"
#include <string>

using namespace std;

class Texture {
public:
	Texture();
	Texture(SDL_Renderer *renderer, const string& fileName);
	Texture(SDL_Renderer *renderer, const string& text, const Font *font,
			const SDL_Color& color);
	virtual ~Texture();

	inline int getWidth() {
		return width_;
	}

	inline int getHeight() {
		return height_;
	}

	inline bool isReady() {
		return texture_ != nullptr;
	}

	// load from image or text, in both cases we should provide a rendered
	bool loadFromImg(SDL_Renderer *renderer, const string& fileName);
	bool loadFromText(SDL_Renderer *renderer, const string& text, const Font *font,
			const SDL_Color& color = { 0, 0, 0, 255 });

	// render the complete texture at position (x,y).
	void render(int x, int y) const;

	// render part of the texture (clip) to a destination rectangle, if no
	// clip provided it renders all texture (scaled to dest).
	void render(const SDL_Rect &dest) const;
	void render(const SDL_Rect &dest, const SDL_Rect& clip) const;

	// render part of the texture (clip) to a destination rectangle with a rotation,
	// if no clip provided it renders all texture (scaled to dest).
	void render(const SDL_Rect &dest, double angle,	const SDL_Rect &clip) const;
	void render(const SDL_Rect &dest, double angle) const;

	void close();

private:
	SDL_Texture *texture_;
	SDL_Renderer *renderer_;
	int width_;
	int height_;
};
