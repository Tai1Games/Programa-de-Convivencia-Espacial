﻿#pragma once
#include <list>
#include "PlayState.h"
#include "GameMode.h"
#include "Entity.h"
#include "checkML.h"
#include "collisionHandler.h"
#include "Resources.h"
#include "MatchInfo.h"
#include "BananaPool.h"
#include "BulletPool.h"
#include "ConfettiPool.h"

using namespace std;

// esta clase es equivalente a un nivel del juego
//se espera que herede de gamestate en un futuro
//tambien deberia convertirse en un template de modo de juego y mapa
class PlayableMenuState : public GameState
{
private:
	string tilemap = "";
	TileMap* tmap = nullptr;
	b2World* physicsWorld_ = nullptr;
	double secondsPerFrame_ = 0;
	CollisionHandler* collisionHandler_ = nullptr;
	Texture* fondo_ = nullptr;


	vector<MatchInfo::PlayerInfo*>* playerInfo;
public:
	PlayableMenuState() {};
	virtual ~PlayableMenuState();
	
	virtual void init() override;
	virtual void update() override;
	virtual void render() override;
	virtual void handleInput() override;
};
