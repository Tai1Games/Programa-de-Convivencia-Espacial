#include "TileMap.h"
#include "SDL_Game.h"
#include "Resources.h"
#include "json.hpp"

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
	loadTileson("../../assets/game/tilemaps/TD_TilemapBitCSV.json");
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

void TileMap::drawTMap() {
	//https://github.com/SSBMTonberry/tileson
	//lo he adaptado a SDL
	//creo que puedo optimizarlo, pero eso para cuando funcione
	//hay que encontrar una forma de emparejar estas cositas
	tson::Tileset* tileset = tMap_.getTileset("modded_colored");
	Texture* tilesetT_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::DebugTilemap);

	for (tson::Layer tileLayer : tMap_.getLayers())
	{
		int firstId = tileset->getFirstgid(); //First tile id of the tileset
		int columns = tileset->getColumns(); //For the demo map it is 8.
		int rows = tileset->getTileCount() / columns;
		int lastId = (tileset->getFirstgid() + tileset->getTileCount()) - 1;

		for (auto& layer : tMap_.getLayers()) {
			if (tileLayer.getType() == tson::Layer::Type::TileLayer)
			{
				//pos = position in tile units
				for (auto& [pos, tile] : tileLayer.getTileData()) //Loops through absolutely all existing tiles
				{
					if (tile != nullptr)
					{
#if USE_CPP17_FILESYSTEM
						fs::path imagePath;
						std::string pathStr;
#else
						std::string imagePath;
#endif
						//With this, I know that it's related to the tileset above (though I only have one tileset)
						if (tile->getId() >= firstId && tile->getId() <= lastId)
						{
#if USE_CPP17_FILESYSTEM
							imagePath = tileset->getImagePath();
							pathStr = imagePath.u8string();
#else
							imagePath = tileset->getImagePath();
#endif
						}

						//Get position in pixel units
						tson::Vector2i position = { std::get<0>(pos) * tMap_.getTileSize().x,std::get<1>(pos) * tMap_.getTileSize().y };

						int baseTilePosition = (tile->getId() - firstId); //This will determine the base position of the tile.
						int spacing = tileset->getSpacing();

						//The baseTilePosition can be used to calculate offset on its related tileset image.
						int currentCol = (baseTilePosition % columns);
						int currentRow = (baseTilePosition / columns);
						//int offsetX = (tileModX != 0) ? ((tileModX)*tMap_.getTileSize().x) : (0 * tMap_.getTileSize().x);
						int offsetX = currentCol * (tMap_.getTileSize().x+spacing);
						/*int offsetY = (currentRow < rows - 1) ? (currentRow * tMap_.getTileSize().y) :
							((rows - 1) * tMap_.getTileSize().y);*/
						int offsetY = (currentRow) * (tMap_.getTileSize().y+spacing);

						SDL_Rect drawPos = { position.x,position.y,tMap_.getTileSize().x,tMap_.getTileSize().y };
						SDL_Rect tilesetClip = { offsetX,offsetY,tMap_.getTileSize().x ,tMap_.getTileSize().y };
						tilesetT_->render(drawPos, tilesetClip);

						//Here you can determine the offset that should be set on a sprite
						//Example on how it would be done using SFML (where sprite presumably is a member of a generated game object):
						//sprite.setTextureRect({offsetX, offsetY, map.getTileSize().x, map.getTileSize().y});
						//sprite.setPosition({position.x, position.y}); 
					}
				}
			}
		}
	}
}

void TileMap::drawTile(tson::Tile* t) {

}

void TileMap::loadTileson(string path) {
	tson::Tileson parser;
	tMap_ = parser.parse(fs::path(path));

	if (tMap_.getStatus() == tson::Map::ParseStatus::OK) {
		cout << "Parseado correctamente por fin" << endl;
		tson::Tileset* t = tMap_.getTileset("modded_colored");
		if (t != nullptr)
			cout << "No se como pero esta cosa ha parseado y pillado el tileset a la primera" << endl;
	}
}
