#pragma once
#include "Component.h"
#include "Entity.h"
#include "Collider.h"

class Pickable : public Component
{
private:
	Collider* mainCollider_ = nullptr;
	b2WeldJoint* joint_ = nullptr;
	bool picked_ = false;
protected:
public:
	Pickable(): Component(ComponentType::Pickable){}
	~Pickable(){};
	virtual void init() override;
	virtual void update() override;
	/*Crea un joint entre el collider del objeto y el collider del jugador enviado como parametro*/
	void PickObjectBy(Collider* player);
	/*Muestra si el objeto ya está unido por un joint a un jugador*/
	bool IsPicked() { return picked_; }
	/*Destruye el joint entre el objeto y el jugador*/
	void UnPickObject();
};

