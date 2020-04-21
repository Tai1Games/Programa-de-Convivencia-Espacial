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


struct PlayerInfo
{
	bool isNear = false;
	Hands* playerHands = nullptr;
	Health* playerHealth = nullptr;
	Wallet* playerWallet = nullptr;
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

	/*Vector que informa de los jugadores que est�n cerca/dentro del trigger y su respectivo Weapon*/
	std::vector<PlayerInfo> playerInfo_;
	std::vector<EnemyData>playersInsideRange_;

	Viewer* vw_ = nullptr;
	Collider* mainCollider_ = nullptr;
	InputHandler* ih_ = nullptr;
	/*Mano que coge este objeto*/
	Hands* currentHand_ = nullptr;

	int impactDamage_ = 0;
	int actionTime = 0;
	int index = 2;

	int calculateCoinsDropped(int coinsPlayer);

public:
	Weapon(WeaponID wId, int impctDmg) : Component(ComponentType::Weapon), weaponType_(wId), impactDamage_(impctDmg){}
	Weapon(ComponentType::CmpId compType, WeaponID wId, int impactDmg) : Component(compType), weaponType_(wId), impactDamage_(impactDmg) {}
	virtual ~Weapon(){};
	virtual void init() override;
	/*Se comprueba que jugador ha pulsado Y y est� cerca para recoger este objeto*/
	virtual void update() override;

	virtual void handleInput() override;

	virtual void onCollisionEnter(Collision* c);
	virtual void onCollisionExit(Collision* c);

	/*Desactiva el arma y se anade a la mano este arma*/
	void PickObjectBy(Hands* playerHands);
	/*Muestra si el objeto ya esta sujeto por una mano*/
	bool IsPicked() { return picked_; }
	/*Reactiva el arma y la lanza en direccion de la mano*/
	virtual void UnPickObject();
	/*Guarda la informacion del jugador que esta dentro del trigger*/
	void SavePlayerInfo(int index, Hands* playerH, Health* healthAux, Wallet* walletAux);
	/*Borra la informacion del jugador que sale del trigger*/
	void DeletePlayerInfo(int index);

	void detectPlayer(Entity* playerDetected, int id);
	void loseContactPlayer(Entity* playerDetected, int id);

	int getImpactDamage() { return impactDamage_; }
	int getWeaponType() { return weaponType_; }
	Hands* getCurrentHand() { return currentHand_; }

	int getPlayerId(); //Cuerpo en el cpp por temas de inclusi�n circular
};

