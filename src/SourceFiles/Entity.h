#pragma once

#include <iostream>
#include <array>
#include <vector>
#include "Component.h"
#include "SDL_Game.h"
#include "checkML.h"
#include "checkML.h"

class EntityManager;
class Component;
struct Collision;

class Entity
{
private:
	EntityManager* entityManager_ = nullptr;

	std::vector<unique_ptr<Component>> components_;
	std::array<Component*, ComponentType::maxComponents> componentsArray_ = {};

	bool active_ = true;
public:
	Entity() {};
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

	bool hasComponent(ComponentType::CmpIdType id) const {
		return componentsArray_[id] != nullptr;
	}

	void update();
	void render();
	void handleInput();

	void setEntityManager(EntityManager* eMan) { entityManager_ = eMan; }

	void setActive(bool active) { active_ = active; }
	bool isActive() { return active_; }

	virtual void onCollisionEnter(Collision* c);
	virtual void onCollisionStay(Collision* c);
	virtual void onCollisionExit(Collision* c);
};
