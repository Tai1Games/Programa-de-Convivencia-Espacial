#include "TileMap.h"
#include "SDL_Game.h"
#include "Resources.h"

int lvl1[9][16] = {
	{1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0},
	{0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
TileMap::TileMap() {
	SDLTexturesManager* tm = SDL_Game::instance()->getTexturesMngr();
	tinkyT_ = tm->getTexture(Resources::Tinky);
	debugT_ = tm->getTexture(Resources::Debug);
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9; column++) {
			map_[row][column] = lvl1[row][column];
		}
	}
	loadTileson("../../assets/tilemaps/TD_TilemapBit.json");
}

void TileMap::drawMap() {
	int t = 0;
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			t = map_[row][column];

			switch (t)
			{
			case (1):
				tinkyT_->render({ column*SIZE,row* SIZE,SIZE,SIZE });
				break;
			case (0):
				debugT_->render({ column * SIZE,row * SIZE,SIZE,SIZE });
				break;
			default:
				
				break;
			}
		}
	}
}

void TileMap::loadTileson(string path) {
	tson::Tileson parser;
	tson::Map map = parser.parse(fs::path(path));

	if (map.getStatus() == tson::Map::ParseStatus::OK) {
		cout << "Parseado correctamente por fin" << endl;
		tson::Tileset* t = map.getTileset("modded_colored");
		if (t != nullptr)
			cout << "No se como pero esta cosa ha parseado y pillado el tileset a la primera" << endl;
	}
}
