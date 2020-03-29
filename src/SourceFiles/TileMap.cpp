#include "TileMap.h"
#include "SDL_Game.h"
#include "Resources.h"
#include "json.hpp"

TileMap::TileMap(int w, int h,string map):Component(ComponentType::Tilemap),  //w y h son de la ventana
width_(w),
height_(h),
tm_(nullptr){
	loadTileson(map);
}

TileMap::~TileMap() {
	tm_ = nullptr;
}

void TileMap::init() {
	tm_ = SDL_Game::instance()->getTexturesMngr();
}
void TileMap::update() {
	//apaño para que draw sea const
	layers_ = tMap_.getLayers();
}
void TileMap::draw() const {
	//código bastante modificado basado en https://github.com/SSBMTonberry/tileson 
	//He añadido sistema de escalado
	//soporte automático para varios tilesets
	//soporte de texturas de SDL
	
	Texture* tilesetT_;//Textura del tileset a utilizar
	const tson::Tileset* tSet;//Datos del tileset a utilizar
	
	//recorremos todas las capas del mapa
	for (auto& tileLayer : layers_)
	{
		//podemos distinguir entre capas de tiles, objetos, imagenes más adelante
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
					if (i < tileSets_.size())
						tSet = &tileSets_[i];
					else throw exception("No se encontró el tileset");

					//variables auxiliares para el dibujado del tile
					int firstId = tSet->getFirstgid(); //First tile id of the tileset
					int tSetColumns = tSet->getColumns();
					int tSetRows = tSet->getTileCount() / tSetColumns;
					int lastId = (tSet->getFirstgid() + tSet->getTileCount()) - 1;
					int tileWidth = tSet->getTileSize().x;
					int tileHeight = tSet->getTileSize().y;
					int spacing = tSet->getSpacing();
					int margin = tSet->getMargin();


					tilesetT_ = tm_->getTexture(Resources::tilesetTag_.find(tSet->getName())->second);;
					//Posicion de dibujado del vector
					tson::Vector2i position = { std::get<0>(pos) * width_ /mapCols_,std::get<1>(pos) * height_ / mapRows_ };

					//posicion unidimensional del tile en el tileset
					int baseTilePosition = (tile->getId() - firstId); //This will determine the base position of the tile.

					//fila y columna del tile en el tileset
					int currentCol = (baseTilePosition % tSetColumns);
					int currentRow = (baseTilePosition / tSetRows);

					//posiciones del tile en el tileset
					int offsetX = currentCol * (tileWidth+spacing);
					int offsetY = (currentRow) * (tileHeight+margin);

					SDL_Rect drawPos = { position.x,position.y,width_ / mapCols_,height_/mapRows_ };
					SDL_Rect tilesetClip = { offsetX,offsetY,tileWidth ,tileWidth};
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
		//variables de escala
		mapCols_ = tMap_.getSize().x;
		mapRows_ = tMap_.getSize().y;
		//guardamos los datos de los tilesets que se usan
		tileSets_ = tMap_.getTilesets();
		return true;
	}
	else
		return false;
}
