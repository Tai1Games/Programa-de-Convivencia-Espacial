#pragma once
#include "Entity.h"
#include "Collider.h"
#include "checkML.h"
#include "PlayerData.h"
#include "InputBinder.h"

class AttachesToObjects : public Component
{
private:
	int playerNumber_;

	Collider* mainCollider_ = nullptr; //Collider del objeto principal (el Tinky)
	Collider* attachedCollider_ = nullptr; //Collider del objeto agarrado
	b2Body* attachedObject_ = nullptr; //Este ser� el collider con el que colisionara y se agarrara
	b2WeldJoint* joint_ = nullptr; //Joint entre el jugador y otro objeto
	PlayerData* playerData_ = nullptr;
	InputBinder* ib;
	KeyboardBinder* kBinder_ = nullptr;

	b2Vec2 normalOnAttach_ = b2Vec2(0, 0);
	float angleOnAttach_ = 0; //angle of attached body on start of attachmemt
public:
	AttachesToObjects() : Component(ComponentType::AttachesToObjects) {};
	~AttachesToObjects() {};

	void attachToObject(b2Body* attachableObject, b2Vec2 collPoint, b2Vec2 collNormal); //Ata al jugador a otro collider
	void deAttachFromObject(); //Rompe el joint entre el jugador y el otro objeto
	bool canAttachToObject(); //Comprueba si el jugador est� pulsando la tecla v�lida y si no est� sujeto a otro objeto
	bool isAttached(); //Te dice si actualmente est� agarrado a algo o no
	Collider* getAttachedObject() { return attachedCollider_; }

	virtual void init() override;
	virtual void handleInput();
	virtual void onCollisionEnter(Collision* c);
	b2Vec2 getAttachmentNormal();
	float getRotationDifference(); //returns the rotation of the attached body since start
};