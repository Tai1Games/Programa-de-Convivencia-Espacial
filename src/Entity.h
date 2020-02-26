#pragma once

#include <iostream>
#include <array>
#include <vector>
#include "Component.h"
#include "SDL_Game.h"

class EntityManager;

class Entity
{
public:
	Entity(SDL_Game* game, EntityManager* mngr);
	virtual ~Entity();

	EntityManager* getEntityMangr() {
		return mngr_;
	}

	template<typename T, typename ... TArgs>
	T* addComponent(TArgs&& ...mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		std::unique_ptr<Component> uPtr(c);
		components_.push_back(std::move(uPtr));
		componentsArray_[c->getId()] = c;
		c->setEntity(this);
		c->setGame(game_);
		c->init();
		return c;
	}

	template<typename T>
	T* getComponent(ComponentType::CmpIdType id) {
		return static_cast<T*>(componentsArray_[id]);
	}

	bool hasComponent(ComponentType::CmpIdType id) {
		return componentsArray_[id] != nullptr;
	}

	void update() {
		for (auto& c : components_) {
			c->update();
		}
	}

	void draw() {
		for (auto& c : components_) {
			c->draw();
		}
	}
private:
	SDL_Game* game_;
	EntityManager* mngr_;

	std::vector<unique_ptr<Component>> components_;
	std::array<Component*, ComponentType::maxComponents> componentsArray_ = {};
};

