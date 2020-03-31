#pragma once
#include "Texture.h"
#include "Tileson.h"
#include "Component.h"
#include "vector"
#include "EntityManager.h"
#include "WeaponFactory.h"

class TileMap : public Component
{
protected:
	int width_, height_;
	int mapCols_, mapRows_;
	tson::Map tMap_;
	std::vector<tson::Tileset> tileSets_;
	SDLTexturesManager* tm_;
	std::vector<tson::Layer> layers_;
	std::vector<b2Vec2> playerSpawnPoints_;
	b2Vec2 posObjEspecialSpawnPoint_; //mando de la tele, router
	std::vector<b2Vec2> objetosMapaSpawnPoints_; //muebles
	std::vector<b2Vec2> armasSpawnPoints_;

private:
	Texture* debugT_;
	Texture* tinkyT_; 

	b2World* physicsWorld_;
	EntityManager* entityManager_;
public:
	TileMap(int w,int h,string map, EntityManager* entityManager_, b2World* physicsWorld_);
	~TileMap();
	virtual void update() override;
	virtual void init() override;
	virtual void draw() const override;
	bool loadTileson(string path);

	b2Vec2 getPlayerSpawnPoint(int id);
	b2Vec2 getObjSpawnPoint(int id);
	b2Vec2 getArmaSpawnPoint(int id);
	b2Vec2 getObjSpecialSpawnPos() { return posObjEspecialSpawnPoint_; };
};

