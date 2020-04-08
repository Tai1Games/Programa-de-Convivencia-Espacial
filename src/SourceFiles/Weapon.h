#pragma once
#include "Component.h"
#include "Entity.h"
#include "Collider.h"
#include "Viewer.h"
#include "Health.h"
#include "Constants.h"
#include "checkML.h"

class Hands;


struct PlayerInfo
{
	bool isNear = false;
	Hands* playerHands = nullptr;
	Health* playerHealth = nullptr;
};
struct EnemyData{
	int id=-1;
	Entity* enemy = nullptr;
};

class Weapon : public Component
{
protected:
	Collider* mainCollider_ = nullptr;
	bool picked_ = false;
	InputHandler* ih_ = nullptr;
	Viewer* vw_ = nullptr;
	WeaponID weaponType_;
	/*Vector que informa de los jugadores que est�n cerca/dentro del trigger y su respectivo Weapon*/
	std::vector<PlayerInfo> playerInfo_;
	std::vector<EnemyData>playersInsideRange_;
	/*Mano que coge este objeto*/
	Hands* currentHand_ = nullptr;

	int damage_ = 0;
	int impactDamage_ = 0;
	bool coolDown = false;
	int actionTime = 0;
	int index = 2;

public:
	Weapon(WeaponID wId): Component(ComponentType::Weapon), weaponType_(wId){}
	~Weapon(){};
	virtual void init() override;
	/*Se comprueba que jugador ha pulsado Y y est� cerca para recoger este objeto*/
	virtual void update() override;

	virtual void handleInput() override;

	/*Desactiva el arma y se a�ade a la mano este arma*/
	void PickObjectBy(Hands* playerHands);
	/*Muestra si el objeto ya est� sujeto por una mano*/
	bool IsPicked() { return picked_; }
	/*Reactiva el arma y la lanza en direcci�n de la mano*/
	void UnPickObject();
	/*Guarda la informacion del jugador que est� dentro del trigger*/
	void SavePlayerInfo(int index, Hands* playerH, Health* healthAux);
	/*Borra la informacion del jugador que sale del trigger*/
	void DeletePlayerInfo(int index);


	void detectPlayer(Entity* playerDetected, int id);
	void loseContactPlayer(Entity* playerDetected, int id);


	virtual void Action();
	int getDamage(){ return damage_; }
	int getImpactDamage() { return impactDamage_; }
	int getWeaponType() { return weaponType_; }
	Hands* getCurrentHand() { return currentHand_; }

	bool isOnHit();
	int getPlayerId(); //Cuerpo en el cpp por temas de inclusi�n circular
};

