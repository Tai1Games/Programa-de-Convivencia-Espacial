#pragma once

#include <SDL.h>

#include "ComponentType.h"
#include "SDL_Game.h"
#include "checkML.h"

class Entity;
struct Collision;

class Component {
protected:
	Entity* entity_;
	SDL_Game* game_;
	ComponentType::CmpId id_;

	//Las clases que hereden de este tendrán un estado propio
public:
	Component(ComponentType::CmpId id);
	virtual ~Component();

	void setEntity(Entity* entity) {
		entity_ = entity;
	}

	void setGame(SDL_Game* game) {
		game_ = game;
		
	}

	void setId(ComponentType::CmpId id) {
		id_ = id;
	}

	ComponentType::CmpId getId() const {
		return id_;
	}

	//Metodos que implementan los hijos y los dotan de funcionalidad
	virtual void init() {};
	virtual void update() {};
	virtual void draw() const {};
	virtual void handleInput() {};
	virtual void onCollisionEnter(Collision* c) {};
	virtual void onCollisionStay(Collision* c) {};
	virtual void onCollisionExit(Collision* c) {};

	Entity* getEntity() { return entity_; };
};


