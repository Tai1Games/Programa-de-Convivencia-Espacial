#pragma once
#include "Texture.h"
#include "Tileson.h"
#include "Component.h"
#include "vector"
#include "EntityManager.h"
#include "WeaponFactory.h"
#include "checkML.h"

class TileMap : public Component
{
protected:
	tson::Map tMap_;
	int width_, height_;
	int mapCols_, mapRows_;
	std::vector<tson::Tileset> tileSets_;
	std::vector<tson::Layer> layers_;

	std::vector<b2Vec2> playerSpawnPoints_;
	b2Vec2 specialObjectsSpawnPoint_; //mando de la tele, router

private:
	Texture* debugT_;
	Texture* tinkyT_; 

	b2World* physicsWorld_;
	EntityManager* entityManager_;
	vector<tson::Object> factoryItems_;
public:
	TileMap(int w,int h,string map, EntityManager* entityManager_, b2World* physicsWorld_);
	~TileMap();
	virtual void update() override;
	virtual void init() override;
	virtual void draw() const override;
	bool loadTileson(string path);
	void executeMapFactory();

	b2Vec2 getPlayerSpawnPoint(int id);
	b2Vec2 getObjSpecialSpawnPos() { return specialObjectsSpawnPoint_; };
};

