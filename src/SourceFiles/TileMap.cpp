#include "TileMap.h"
#include "SDL_Game.h"
#include "Resources.h"
#include "json.hpp"

TileMap::TileMap(int w, int h):Component(ComponentType::Tilemap),
width_(w),
height_(h) {
	SDLTexturesManager* tm = SDL_Game::instance()->getTexturesMngr();
	tinkyT_ = tm->getTexture(Resources::Tinky);
	debugT_ = tm->getTexture(Resources::Debug);
	loadTileson("../../assets/game/tilemaps/TD_TilemapBitCSV.json");
}

TileMap::~TileMap() {

}

void TileMap::drawTMap() {
	//https://github.com/SSBMTonberry/tileson
	//lo he adaptado a SDL.
	//creo que puedo optimizarlo, pero eso para cuando funcione
	//hay que encontrar una forma de emparejar estas cositas
	Texture* tilesetT_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::tilesetTag_.find("modded_colored")->second);
	tson::Tileset* tSet = tMap_.getTileset("modded_colored");
	for (tson::Layer tileLayer : tMap_.getLayers())
	{

		if (tileLayer.getType() == tson::Layer::Type::TileLayer)
		{
			//pos = position in tile units
			for (auto& [pos, tile] : tileLayer.getTileData()) //Loops through absolutely all existing tiles
			{
				if (tile != nullptr)
				{
					//buscamos el tileset correspondiente
					int i = 0;
					int id = tile->getId();
					while (i<tileSets_.size() 
						&& !(id >= tileSets_[i].getFirstgid()
						&& id <= (tileSets_[i].getFirstgid() + tileSets_[i].getTileCount()) - 1))
					{
						i++;
					}
					if(i<tileSets_.size())
						tSet = &tileSets_[i];

					int firstId = tSet->getFirstgid(); //First tile id of the tileset
					int tSetColumns = tSet->getColumns();
					int tSetRows = tSet->getTileCount() / tSetColumns;
					int lastId = (tSet->getFirstgid() + tSet->getTileCount()) - 1;
					int tileWidth = tSet->getTileSize().x;
					int tileHeight = tSet->getTileSize().y;
					int spacing = tSet->getSpacing();


					tilesetT_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::tilesetTag_.find(tSet->getName())->second);;
					//Get position in pixel units
					tson::Vector2i position = { std::get<0>(pos) * width_ /mapCols_,std::get<1>(pos) * height_ / mapRows_ };

					int baseTilePosition = (tile->getId() - firstId); //This will determine the base position of the tile.

					//The baseTilePosition can be used to calculate offset on its related tileset image.
					int currentCol = (baseTilePosition % tSetColumns);
					int currentRow = (baseTilePosition / tSetRows);
					//int offsetX = (currentRow != 0) ? ((currentRow)*tMap_.getTileSize().x) : (0 * tMap_.getTileSize().x);
					int offsetX = currentCol * (tileWidth+spacing);
					/*int offsetY = (currentRow < rows - 1) ? (currentRow * tMap_.getTileSize().y) :
						((rows - 1) * tMap_.getTileSize().y);*/
					int offsetY = (currentRow) * (tileHeight+spacing);

					SDL_Rect drawPos = { position.x,position.y,width_ / mapCols_,height_/mapRows_ };
					SDL_Rect tilesetClip = { offsetX,offsetY,tileWidth ,tileWidth};
					//if(id == 1107)
						tilesetT_->render(drawPos, tilesetClip);
				}
			}
		}
	}
}

bool TileMap::loadTileson(string path) {
	tson::Tileson parser;
	tMap_ = parser.parse(fs::path(path));
	if (tMap_.getStatus() == tson::Map::ParseStatus::OK) {
		//guardamos todas las texturas de los tileset
		mapCols_ = tMap_.getSize().x;
		mapRows_ = tMap_.getSize().y;
		tileSets_ = tMap_.getTilesets();
		tSetTextures_.reserve(tileSets_.size());
		for (tson::Tileset tileset : tileSets_) {
			string name = tileset.getName();
			tSetTextures_.push_back(
				SDL_Game::instance()->getTexturesMngr()
				->getTexture(Resources::tilesetTag_.find(name)->second));
		}
	}
	else
	return false;
}
