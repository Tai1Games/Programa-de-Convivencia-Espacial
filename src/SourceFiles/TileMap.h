#pragma once
#include "Texture.h"
#include "Tileson.h"
class TileMap
{
protected:
	int map_[9][16];
	std::pair<int, int> res_; //resolucion de la pantalla
	const int SIZE = 32;
private:
	Texture* debugT_;
	Texture* tinkyT_; 
public:
	TileMap();
	~TileMap();
	void drawMap();
	void loadTileson(string path);
};

