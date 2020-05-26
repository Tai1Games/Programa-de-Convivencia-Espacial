#pragma once

#include <SDL_ttf.h>
#include <string>
#include "checkML.h"


using namespace std;

class Font {
public:
	Font();
	Font(const string& fileName, int size);
	virtual ~Font();

	bool load(const string& fileName, int size);
	void close();
	SDL_Surface* renderText(const string& text, SDL_Color color, Uint32 wrapLength) const;
private:
	TTF_Font* font_;
};
