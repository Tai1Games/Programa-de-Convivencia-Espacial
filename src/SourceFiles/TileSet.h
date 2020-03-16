#pragma once
#include "../json/single_include/nlohmann/json.hpp"
#include <string>
#include "Texture.h"
#include <vector>

using json = nlohmann::json;

class TileSet
{
protected:
	int tileW_, tileH_;
	int vMargin_, hMargin_;
	vector<SDL_Rect> clips_;
	Texture* tileSet_;
private:
public:
	TileSet();
	TileSet(Texture* set, int w, int h, int mH = 0, int mV = 0);
	~TileSet();
	void loadSet(Texture* set, int w, int h, int mH = 0, int mV = 0);
};

