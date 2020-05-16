#pragma once
#include "Texture.h"
#include "Tileson.h"
#include "Component.h"
#include "vector"
#include "EntityManager.h"
#include "ObjectFactory.h"
#include "WeaponFactory.h"
#include "checkML.h"


class BoilerButtonLogic;
class FireBallGenerator;
class ConfettiPool;
class TomatoPool;
class BananaPool;
class GameMode;

class TileMap : public Component
{
protected:
	tson::Map tMap_;
	int width_, height_;
	int mapCols_, mapRows_;
	std::vector<tson::Tileset> tileSets_;
	std::vector<tson::Layer> layers_;

	std::vector<b2Vec2> playerSpawns_;
	b2Vec2 specialObjectsSpawnPoint_; //mando de la tele, router
	std::vector<b2Vec2> coinsSpawnPoints_; //guarda posicions monedas
	FireBallGenerator* boilerAux_ = nullptr;
	std::vector<BoilerButtonLogic*> boilerButtons_;

private:
	Texture* debugT_;
	Texture* tinkyT_;

	b2World* physicsWorld_;
	EntityManager* entityManager_;
	vector<tson::Object> factoryItems_;

	std::vector<b2Vec2> lowTierWeaponSpawnPoints_;
	std::vector<b2Vec2> midTierWeaponSpawnPoints_;
	std::vector<b2Vec2> highTierWeaponSpawnPoints_;

	ConfettiPool* confettiPool_;
	BulletPool* bulletPool_ = nullptr;
	unique_ptr<TomatoPool> tomatoPool_;
	unique_ptr<BananaPool> bananaPool_;

	GameMode* gameMode_ = nullptr;

	void solvePostCreationProblems(); //Called when reading of tilemap ends. Use this to assign references and solve similar problems.
public:
	TileMap(int w, int h, string map, EntityManager* entityManager_, b2World* physicsWorld_, BulletPool* bp, ConfettiPool* cP, GameMode* gameMode);
	~TileMap();
	virtual void update() override;
	virtual void init() override;
	virtual void draw() const override;
	bool loadTileson(string path);
	void executeMapFactory();
	void createWeapons();

	b2Vec2 getPlayerSpawnPoint(int id);
	b2Vec2 getObjSpecialSpawnPos() { return specialObjectsSpawnPoint_; };
	std::vector<b2Vec2> getCoinsSpawnPoints() { return coinsSpawnPoints_; }
	FireBallGenerator* getFireballGen() { return boilerAux_; }
};

