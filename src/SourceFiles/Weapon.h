#pragma once
#include "Component.h"
#include "Entity.h"
#include "Collider.h"
#include "Viewer.h"

class Hands;

struct PlayerInfo
{
	bool isNear = false;
	Hands* playerHands = nullptr;
};

enum WeaponID {
	NoWeapon,
	BlueTinky,
	RedTinky,
	PinkTinky,

	WEAPON_NUMBER
};

class Weapon : public Component
{
private:
	Collider* mainCollider_ = nullptr;
	bool picked_ = false;
	InputHandler* ih_ = nullptr;
	Viewer* vw_ = nullptr;
	WeaponID weaponType_;
	/*Vector que informa de los jugadores que están cerca/dentro del trigger y su respectivo body*/
	std::vector<PlayerInfo> playerInfo_;
	/*Mano que coge este objeto*/
	Hands* currentHand_ = nullptr;
public:
	Weapon(Weapon::WeaponID wId): Component(ComponentType::Weapon), weaponType_(wId){}
	~Weapon(){};
	virtual void init() override;
	/*Se comprueba que jugador ha pulado Y y está cerca para recoger este objeto*/
	virtual void update() override;
	/*Crea un joint entre el collider del objeto y el collider del jugador enviado como parametro*/
	void PickObjectBy(Hands* playerHands);
	/*Muestra si el objeto ya está unido por un joint a un jugador*/
	bool IsPicked() { return picked_; }
	/*Destruye el joint entre el objeto y el jugador*/
	void UnPickObject();
	/*Guarda la informacion del jugador que está dentro del trigger*/
	void SavePlayerInfo(int index, Hands* playerH);
	/*Borra la informacion del jugador que sale del trigger*/
	void DeletePlayerInfo(int index);
	int getWeaponType() { return weaponType_; }
};

