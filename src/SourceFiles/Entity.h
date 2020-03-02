#pragma once

#include <iostream>
#include <array>
#include <vector>
#include "Component.h"
#include "SDL_Game.h"
#include "checkML.h"


class EntityManager;
class Component;

class Entity
{
public:
	Entity(EntityManager* mngr);
	virtual ~Entity();

	EntityManager* getEntityManager() {
		return entityManager_;
	}

	template<typename T, typename ... TArgs>
	T* addComponent(TArgs&& ...mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		std::unique_ptr<Component> uPtr(c);
		components_.push_back(std::move(uPtr));
		componentsArray_[c->getId()] = c;
		c->setEntity(this);
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

	void update();
	void render();
	void handleInput();

private:
	EntityManager* entityManager_;

	std::vector<unique_ptr<Component>> components_;
	std::array<Component*, ComponentType::maxComponents> componentsArray_ = {};

};

