#pragma once
#include "Entity.h"
#include "Collider.h"
#include "checkML.h"

class AttachesToObjects : public Component
{
private:
	Collider* mainCollider_ = nullptr; //Collider del objeto principal (el Tinky)
	b2Body* attachedObject_ = nullptr; //Este será el collider con el que colisionara y se agarrara
	b2WeldJoint* joint_ = nullptr; //Joint entre el jugador y otro objeto
	int playerNumber_; //Número del jugador (de 1 a 4)
public:
	AttachesToObjects(int playerNumber) : Component(ComponentType::AttachesToObjects) { playerNumber_ = playerNumber; };
	~AttachesToObjects() {};
	void attachToObject(b2Body* attachableObject, b2Vec2 collPoint); //Ata al jugador a otro collider
	void deAttachFromObject(); //Rompe el joint entre el jugador y el otro objeto
	bool canAttachToObject(); //Comprueba si el jugador está pulsando la tecla válida y si no está sujeto a otro objeto
	bool isAttached(); //Te dice si actualmente está agarrado a algo o no
	virtual void init() override;
	virtual void handleInput();
};