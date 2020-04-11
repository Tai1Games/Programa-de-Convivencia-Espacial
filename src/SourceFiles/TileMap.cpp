#include "TileMap.h"
#include "SDL_Game.h"
#include "Resources.h"
#include "json.hpp"
#include <string>


TileMap::TileMap(int w, int h, string map, EntityManager* eM, b2World* pW) :Component(ComponentType::Tilemap),  //w y h son de la ventana
width_(w),
height_(h),
entityManager_(eM),
physicsWorld_(pW){
	loadTileson(map);
}

TileMap::~TileMap() {
}

void TileMap::init() {
	layers_ = tMap_.getLayers();
	//recorremos todas las capas del mapa
	for (auto& tileLayer : layers_)
	{
		//podemos distinguir entre capas de tiles, objetos, imagenes más adelante
		if (tileLayer.getType() == tson::Layer::Type::ObjectGroup)
		{
			//pos = position in tile units
			vector<tson::Object> objetos = tileLayer.getObjects();
			for (auto obj : objetos)
			{
				if (tileLayer.getName() == "Walls") { //muros
					factoryItems_.push_back(obj);
				}
				else if (tileLayer.getName() == "Spawns") { //spawns
					playerSpawnPoints_.push_back(b2Vec2(obj.getPosition().x / CONST(double, "PIXELS_PER_METER"), (CONST(int, "WINDOW_HEIGHT") - obj.getPosition().y) / CONST(double, "PIXELS_PER_METER"))); //añade la posicion al vector de spawns
				}
				else if (tileLayer.getName() == "SpecialObject"){ //objetos espaciales (mando de tele, router...)
					specialObjectsSpawnPoint_ = b2Vec2(obj.getPosition().x / CONST(double, "PIXELS_PER_METER"), (CONST(int, "WINDOW_HEIGHT") - obj.getPosition().y) / CONST(double, "PIXELS_PER_METER"));
				}
				else if (tileLayer.getName() == "MapObjects") { //muebles
					factoryItems_.push_back(obj);
				}
				else if (tileLayer.getName() == "Weapons") {
					factoryItems_.push_back(obj);
				}
				else if (tileLayer.getName() == "CoinSpawners") {
					coinsSpawnPoints_.push_back(b2Vec2(obj.getPosition().x / CONST(double, "PIXELS_PER_METER"), (CONST(int, "WINDOW_HEIGHT") - obj.getPosition().y) / CONST(double, "PIXELS_PER_METER")));
				}
			}
		}
	}
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
					while (i < tileSets_.size()
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


					tilesetT_ = SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::tilesetTag_.find(tSet->getName())->second);;
					//Posicion de dibujado del vector
					tson::Vector2i position = { std::get<0>(pos) * width_ / mapCols_,std::get<1>(pos) * height_ / mapRows_ };

					//posicion unidimensional del tile en el tileset
					int baseTilePosition = (tile->getId() - firstId); //This will determine the base position of the tile.

					//fila y columna del tile en el tileset
					int currentCol = (baseTilePosition % tSetColumns);
					int currentRow = (baseTilePosition / tSetRows);

					//posiciones del tile en el tileset
					int offsetX = currentCol * (tileWidth + spacing);
					int offsetY = (currentRow) * (tileHeight + margin);

					SDL_Rect drawPos = { position.x,position.y,width_ / mapCols_,height_ / mapRows_ };
					SDL_Rect tilesetClip = { offsetX,offsetY,tileWidth ,tileWidth };
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

void TileMap::executeMapFactory()
{
	for (auto o : factoryItems_) {
		tson::Vector2i p, s;
		s = o.getSize();
		p = o.getPosition();
		b2Vec2 size;
		//Calculo de posicion para puntos de Tiled (la mayoria de items)
		b2Vec2 pos = b2Vec2(p.x / CONST(double, "PIXELS_PER_METER"), (CONST(int, "WINDOW_HEIGHT") - p.y) / CONST(double, "PIXELS_PER_METER"));
		string name = o.getName();

		if (name == "Wall") {
			//calculo de posicion y tamaño para cajas de Tiled
			size = b2Vec2(s.x / CONST(double, "PIXELS_PER_METER"), (s.y) / CONST(double, "PIXELS_PER_METER"));
			pos = b2Vec2(p.x / CONST(double, "PIXELS_PER_METER") + (size.x / 2), (CONST(int, "WINDOW_HEIGHT") - p.y) / CONST(double, "PIXELS_PER_METER") - (size.y / 2));
			ObjectFactory::makeWall(entityManager_, physicsWorld_, pos, size);
		}
		else if (name == "Ball") {
			ObjectFactory::makeBall(entityManager_, physicsWorld_, pos, b2Vec2(0.5, 0.5));
		}
		else if (name == "Slipper") {
			ObjectFactory::makeSlipper(entityManager_, physicsWorld_, pos, b2Vec2(0.5, 0.5));
		}
		else if (name == "Stapler") {
			ObjectFactory::makeStapler(entityManager_, physicsWorld_, pos, b2Vec2(0.5, 0.5));
		}
		else if (name == "SpaceJunk") {
			ObjectFactory::makeSpaceJunk(entityManager_, physicsWorld_, pos, b2Vec2(0.5, 0.5));
		}
	}
}

b2Vec2 TileMap::getPlayerSpawnPoint(int id)
{
	if (id < playerSpawnPoints_.size()) return playerSpawnPoints_[id];
	else return b2Vec2();
}