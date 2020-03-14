#pragma once
#include "Texture.h"
#include "Tileson.h"
#include "Component.h"
#include "vector"
class TileMap : public Component
{
protected:
	int width_, height_;
	int mapCols_, mapRows_;
	tson::Map tMap_;
	std::vector<tson::Tileset> tileSets_;
	std::vector<Texture*> tSetTextures_;
private:
	Texture* debugT_;
	Texture* tinkyT_; 
public:
	TileMap(int w,int h);
	~TileMap();
	void drawTMap();
	bool loadTileson(string path);
};

