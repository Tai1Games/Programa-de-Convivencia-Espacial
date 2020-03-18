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
	Piedra,
	Pelota,
	Mancuerna,
	Grapadora,
	Extintor,
	Chancla,

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
	/*Vector que informa de los jugadores que están cerca/dentro del trigger y su respectivo Weapon*/
	std::vector<PlayerInfo> playerInfo_;
	/*Mano que coge este objeto*/
	Hands* currentHand_ = nullptr;
	float throwSpeed_ = 150;
	float spinSpeed_ = 8;
public:
	Weapon(Weapon::WeaponID wId): Component(ComponentType::Weapon), weaponType_(wId){}
	~Weapon(){};
	virtual void init() override;
	/*Se comprueba que jugador ha pulsado Y y está cerca para recoger este objeto*/
	virtual void update() override;
	/*Desactiva el arma y se añade a la mano este arma*/
	void PickObjectBy(Hands* playerHands);
	/*Muestra si el objeto ya está sujeto por una mano*/
	bool IsPicked() { return picked_; }
	/*Reactiva el arma y la lanza en dirección de la mano*/
	void UnPickObject();
	/*Guarda la informacion del jugador que está dentro del trigger*/
	void SavePlayerInfo(int index, Hands* playerH);
	/*Borra la informacion del jugador que sale del trigger*/
	void DeletePlayerInfo(int index);
	int getWeaponType() { return weaponType_; }
};

