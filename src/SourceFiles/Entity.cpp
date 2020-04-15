#include "Entity.h"
Entity::Entity(EntityManager* mngr) :
	entityManager_(mngr)
{
}

Entity::~Entity() {
	//cout << "Entity destroyed" << endl;
}

void Entity::update()
{
	for (auto& c : components_) {
		c->update();
	}
}

void Entity::render()
{
	for (auto& c : components_) {
		c->draw();
	}
}

void Entity::handleInput()
{
	for (auto& c : components_) {
		c->handleInput();
	}
}

void Entity::onCollisionEnter(Collision* c)
{
	for (auto& cmp : components_)
		cmp->onCollisionEnter(c);
}
void Entity::onCollisionStay(Collision* c)
{
	for (auto& cmp : components_)
		cmp->onCollisionStay(c);
}
void Entity::onCollisionExit(Collision* c)
{
	for (auto& cmp : components_)
		cmp->onCollisionExit(c);
}

