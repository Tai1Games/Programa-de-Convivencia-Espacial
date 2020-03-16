#include "SDLFontsManager.h"
#include <assert.h>

SDLFontsManager::SDLFontsManager() :
		initialized_(false) {
}

SDLFontsManager::~SDLFontsManager() {
	if (!initialized_)
		return;

	// free all sound effect chucks
	for (const auto &font : fonts_) {
		if (font.second != nullptr)
			delete font.second;
	}

	TTF_Quit();
}

bool SDLFontsManager::init() {
	if (initialized_)
		return false;

	int ttfInit_r = TTF_Init();
	assert(ttfInit_r == 0);
	/*
	 if ( r != 0 ) {
	 throw "Something went wrong with TTF_init";
	 }
	 */
	initialized_ = true;

	return true;
}

Font* SDLFontsManager::getFont(std::size_t tag) {
	return fonts_[tag];
}

bool SDLFontsManager::loadFont(std::size_t tag, const string& fileName, int size) {
	if (!initialized_)
		return false;

	Font *font = new Font();
	if (font->load(fileName, size)) {
		Font *curr = fonts_[tag];
		if (curr != nullptr)
			delete curr;
		fonts_[tag] = font;
		return true;
	} else {
		delete font;
		return false;
	}
}
