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
	SDLTexturesManager* tm_;
	std::vector<tson::Layer> layers_;
private:
	Texture* debugT_;
	Texture* tinkyT_; 
public:
	TileMap(int w,int h,string map);
	~TileMap();
	virtual void update() override;
	virtual void init() override;
	virtual void draw() const override;
	bool loadTileson(string path);
};

