#pragma once

#include <map>
#include "Font.h"
#include "checkML.h"


/*
 *
 */
class SDLFontsManager {
public:
	SDLFontsManager();
	virtual ~SDLFontsManager();

	// supposed to be called before start using the object
	bool init();

	Font* getFont(std::size_t tag);
	bool loadFont(std::size_t tag, const string& fileName, int size);
private:
	map<int, Font*> fonts_;
	bool initialized_;
};

