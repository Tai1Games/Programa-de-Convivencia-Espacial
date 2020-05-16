#pragma once
#include "Component.h"
#include "Entity.h"
#include "Collider.h"
#include "Viewer.h"
#include "Health.h"
#include "Wallet.h"
#include "Constants.h"
#include "checkML.h"


class Hands;
class InputBinder;

//Informacion del jugador que se encuentra en rango del arma
struct PlayerInfo
{
	bool isNear = false;
	Hands* playerHands = nullptr;
	Health* playerHealth = nullptr;
	Wallet* playerWallet = nullptr;
	InputBinder* playerBinder = nullptr;
};
struct EnemyData {
	int id = -1;
	Entity* enemy = nullptr;
};

class Weapon : public Component
{
protected:
	bool picked_ = false;
	WeaponID weaponType_;

	/*Vector que informa de los jugadores que están cerca/dentro del trigger y su respectivo Weapon*/
	std::vector<PlayerInfo> playerInfo_;

	Viewer* vw_ = nullptr;
	Collider* mainCollider_ = nullptr;
	/*Mano que coge este objeto*/
	Hands* currentHand_ = nullptr;

	int pickedIndex_ = -1; //player que tiene el arma, -1 si no la tiene nadie

	int impactDamage_ = 0;	
	int impactForce_ = 0;

	int calculateCoinsDropped(int coinsPlayer);

private:
	double maxThrowSpeed_ = 0;
	double minThrowSpeed_ = 0;
	double spinOnThrowSpeed_ = 0;

	int throwCooldown_ = 0;
	int throwCooldownTimer_ = 0;

public:
	Weapon(WeaponID wId, int impctDmg, int impctForce=0) : Component(ComponentType::Weapon), weaponType_(wId), impactDamage_(impctDmg), impactForce_(impctForce){}
	Weapon(ComponentType::CmpId compType, WeaponID wId, int impactDmg, int impctForce=0) : Component(compType), weaponType_(wId), impactDamage_(impactDmg), impactForce_(impctForce) {}
	virtual ~Weapon(){};
	virtual void init() override;
	virtual void update() override;

	virtual void handleInput() override;

	/*Desactiva el arma y se anade a la mano este arma*/
	virtual void PickObjectBy(int index);
	/*Muestra si el objeto ya esta sujeto por una mano*/
	bool IsPicked() { return picked_; }
	/*Reactiva el arma y la lanza en direccion de la mano*/
	virtual void UnPickObject();

	int getImpactDamage() { return impactDamage_; }
	int getWeaponType() { return weaponType_; }
	Hands* getCurrentHand() { return currentHand_; }
	int getImpactForce() { return impactForce_; }

	int getPlayerId(); //Cuerpo en el cpp por temas de inclusi�n circular

	virtual void onCollisionEnter(Collision* c);
	virtual void onCollisionExit(Collision* c);

	/*Guarda la informacion del jugador que esta dentro del trigger*/
	void SavePlayerInfo(int index, Hands* playerH, Health* healthAux, Wallet* walletAux, InputBinder* binderAux);
	/*Borra la informacion del jugador que sale del trigger*/
	void DeletePlayerInfo(int index);
};

