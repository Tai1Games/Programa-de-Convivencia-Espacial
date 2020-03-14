#pragma once
#include "Entity.h"
#include "Collider.h"
#include "checkML.h"

class AttachesToObjects : public Component
{
private:
	Collider* mainCollider_ = nullptr; //Collider del objeto principal (el Tinky)
	b2Body* bodyToBeAttached = nullptr; //Este será el collider con el que colisionara y se agarrara
	b2Vec2 collPoint_;
	b2WeldJoint* joint_ = nullptr; //Joint entre el jugador y otro objeto
	int playerNumber_;
	bool registeredCollision = false;
public:
	AttachesToObjects(int playerNumber) : Component(ComponentType::AttachesToObjects) { playerNumber_ = playerNumber; };
	~AttachesToObjects() {};
	void attachToObject(); //Ata al jugador a otro collider
	void registerCollision(b2Body* attachableObject, b2Vec2 collPoint);
	void deAttachFromObject(); //Rompe el joint entre el jugador y el otro objeto
	bool isPressingInput();
	virtual void update();
	virtual void init() override;
	virtual void handleInput();
};