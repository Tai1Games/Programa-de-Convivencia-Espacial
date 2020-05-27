#pragma once

#include "Font.h"
#include "Texture.h"
#include <string>
#include <SDL_image.h>
#include <assert.h>
#include <map>
#include "checkML.h"


using namespace std;

class SDLTexturesManager {
public:
	SDLTexturesManager();
	virtual ~SDLTexturesManager();

	// supposed to be called before start using the object
	virtual bool init();

	Texture* getTexture(std::size_t tag) {
		return textures_[tag];
	}
	bool loadFromImg(unsigned char tag, SDL_Renderer* renderer,
		const string& fileName, unsigned short nHorFrames, unsigned short nVerFrames);
	bool loadFromText(unsigned char tag, SDL_Renderer* renderer, const string& text,
		const Font* font, const SDL_Color& color);
private:
	void storeTexture(unsigned char tag, Texture* texture);

	bool initialized_;
	map<std::size_t, Texture*> textures_;
};