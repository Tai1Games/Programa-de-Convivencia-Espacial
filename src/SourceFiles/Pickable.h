#pragma once
#include "Component.h"
#include "Entity.h"
#include "Collider.h"

struct PlayerInfo
{
	bool isNear = false;
	b2Body* body = nullptr;
};

class Pickable : public Component
{
protected:
private:
	Collider* mainCollider_ = nullptr;
	b2WeldJoint* joint_ = nullptr;
	bool picked_ = false;
	InputHandler* ih_ = nullptr;
	/*Vector que informa de los jugadores que están cerca/dentro del trigger y su respectivo body*/
	std::vector<PlayerInfo> playerInfo;
public:
	Pickable(): Component(ComponentType::Pickable){}
	~Pickable(){};
	virtual void init() override;
	virtual void update() override;
	/*Crea un joint entre el collider del objeto y el collider del jugador enviado como parametro*/
	void PickObjectBy(b2Body* playerBody);
	/*Muestra si el objeto ya está unido por un joint a un jugador*/
	bool IsPicked() { return picked_; }
	/*Destruye el joint entre el objeto y el jugador*/
	void UnPickObject();
	/*Guarda la informacion del jugador que está dentro del trigger*/
	void SavePlayerInfo(int index, b2Body* playerB);
	void DeletePlayerInfo(int index);
};

