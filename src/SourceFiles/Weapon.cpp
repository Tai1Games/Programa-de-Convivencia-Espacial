#include "Weapon.h"
#include <iostream>
#include "InputHandler.h"
#include "Hands.h"
#include "Health.h"
#include "Wallet.h"
#include "Collision.h"
#include "ThrownByPlayer.h"

int Weapon::calculateCoinsDropped(int coinsPlayer)
{
	if (coinsPlayer <= CONST(int, "WEAPON_HIGH_TIER_COIN_DAMAGE")) return 3;
	else if (coinsPlayer <= CONST(int, "WEAPON_MID_TIER_COIN_DAMAGE")) return 2;
	else if (coinsPlayer > CONST(int, "WEAPON_MID_TIER_COIN_DAMAGE")) return 1;
	return 0;
}

void Weapon::init()
{
	ih_ = SDL_Game::instance()->getInputHandler();
	mainCollider_ = GETCMP1_(Collider);
	vw_ = GETCMP1_(Viewer);
	//Fixture Sensor a�adido por el componente
	mainCollider_->createRectangularFixture(mainCollider_->getW(0)*4, mainCollider_->getH(0)*4, 1, 0.1, 0, Collider::CollisionLayer::PickableObject, true);
	//Pone la informacion de esta clase en el body, para poder usarla en el Listener
	//Tama�o del vector segun el numero de jugadores
	playerInfo_.resize(4);
}

void Weapon::update()
{
	if (currentHand_ != nullptr && mainCollider_->isEnabled()) {
		mainCollider_->setTransform(b2Vec2(currentHand_->getPos().x, currentHand_->getPos().y), 0.0);	//Colocamos el trigger de golpear
		
		if (coolDown == true) {
			actionTime++; //Incrementamos tiempo de accion de la chancla

			if (actionTime >= CONST(double, "WEAPON_MELEE_TIME")) {
				coolDown = false;
				actionTime = 0;
			}
			else { vw_->setDrawable(false); }
		}
		else { vw_->setDrawable(true); }
	}
}

void Weapon::handleInput()
{
	if (currentHand_ == nullptr) {
		for (int i = 0; i < playerInfo_.size(); i++) {

			if (!IsPicked() && playerInfo_[i].isNear &&
				ih_->isButtonJustDown(i, SDL_CONTROLLER_BUTTON_Y)) {
				cout << "inRange";
				PickObjectBy(playerInfo_[i].playerHands);
			}
		}
	}
	else if (IsPicked() && ih_->isButtonJustDown(currentHand_->getPlayerId(), SDL_CONTROLLER_BUTTON_Y))
	{
		UnPickObject();
	}
}

void Weapon::onCollisionEnter(Collision* c)
{
	Entity* other = c->entity;
	Hands* otherHand = GETCMP2(other, Hands);
	Hands* myHand = getCurrentHand();
	
	if (otherHand != nullptr) {
		SavePlayerInfo(otherHand->getPlayerId(), otherHand, GETCMP2(other, Health), GETCMP2(other, Wallet));
		if (myHand != nullptr && otherHand != myHand) {
			detectPlayer(other, GETCMP2(other, PlayerData)->getId());
		}
	}


}

void Weapon::onCollisionExit(Collision* c)
{
	Hands* otherHand = GETCMP2(c->entity, Hands);

	if (otherHand != nullptr) {
		DeletePlayerInfo(otherHand->getPlayerId());
	}

	PlayerData* playerData = GETCMP2(c->entity, PlayerData);
	if (playerData != nullptr) {
		loseContactPlayer(c->entity, playerData->getPlayerNumber());
	}
}

void Weapon::PickObjectBy(Hands* playerH)
{
	if (playerH->getWeaponID() == NoWeapon) {
		currentHand_ = playerH;
		picked_ = true;
		currentHand_->setWeapon(weaponType_, this);
		if (weaponType_ == WeaponID::Slipper) {
			//Creamos el trigger de ataque
			mainCollider_->createRectangularFixture(mainCollider_->getW(0)*2, mainCollider_->getH(0)*2, 1, 0.1, 0, Collider::CollisionLayer::PickableObject, true);
			//Trigger de la Chancla(Cambiamos con quien colisiona)
			b2Filter aux1 = mainCollider_->getFixture(0)->GetFilterData();
			aux1.categoryBits = Collider::CollisionLayer::Trigger;
			aux1.maskBits = Collider::CollisionLayer::Player;
			mainCollider_->getFixture(1)->SetFilterData(aux1);
			//Caja colision de la chancla
			b2Filter aux = mainCollider_->getFixture(0)->GetFilterData();
			aux.categoryBits = Collider::CollisionLayer::UnInteractableObject;
			aux.maskBits = Collider::CollisionLayer::Wall;
			mainCollider_->getFixture(0)->SetFilterData(aux);
		}
		else mainCollider_->getBody()->SetEnabled(false);
		vw_->setDrawable(false);
	}
}

void Weapon::UnPickObject()
{
	currentHand_->setWeapon(NoWeapon, nullptr);
	picked_ = false;
	if (weaponType_ == WeaponID::Slipper) {
		
		//Trigger de la Chancla(Restairamos sus capas de colision)
		b2Filter aux1 = mainCollider_->getFixture(0)->GetFilterData();
		aux1.categoryBits = Collider::CollisionLayer::PickableObject;
		aux1.maskBits = Collider::CollisionLayer::Player | Collider::CollisionLayer::Wall;
		mainCollider_->getFixture(1)->SetFilterData(aux1);
		//Caja colision de la chancla
		b2Filter aux = mainCollider_->getFixture(0)->GetFilterData();
		aux.categoryBits = Collider::CollisionLayer::NormalObject;
		aux.maskBits= Collider::CollisionLayer::NormalObject | Collider::CollisionLayer::NormalAttachableObject | Collider::CollisionLayer::Player | Collider::CollisionLayer::Wall;
		mainCollider_->getFixture(0)->SetFilterData(aux);
		
	}
	mainCollider_->getBody()->SetEnabled(true);
	vw_->setDrawable(true);
	
	cout <<"dirHand: "<< currentHand_->getDir().x <<", "<< currentHand_->getDir().y<<"\n";
	cout << "dirplayer: " << currentHand_->getVel().x << ", " << currentHand_->getVel().y << "\n";
	
	//Si se tira un objeto, se guarda en el objeto lanzado la ID de quien lo lanza.
	ThrownByPlayer* tObj = GETCMP_FROM_FIXTURE_(mainCollider_->getFixture(0),ThrownByPlayer);
	if (tObj != nullptr) tObj->throwObject(currentHand_->getPlayerId());

	mainCollider_->setLinearVelocity(b2Vec2(0, 0));
	mainCollider_->setTransform(b2Vec2(currentHand_->getPos().x + currentHand_->getDir().x * CONST(double, "ARM_LENGTH_PHYSICS"), currentHand_->getPos().y -currentHand_->getDir().y * CONST(double, "ARM_LENGTH_PHYSICS")), currentHand_->getAngle());
	mainCollider_->applyLinearImpulse(b2Vec2(currentHand_->getDir().x * CONST(double, "WEAPON_THROW_SPEED") + currentHand_->getVel().x, -currentHand_->getDir().y * CONST(double, "WEAPON_THROW_SPEED") + currentHand_->getVel().y), mainCollider_->getBody()->GetLocalCenter());
	mainCollider_->getBody()->SetAngularVelocity(CONST(double, "WEAPON_SPIN_SPEED"));
	currentHand_ = nullptr;
	if (weaponType_ == WeaponID::Slipper) {
		//Destruimos el trigger de ataque
		mainCollider_->destroyFixture(index);
		//index++;	//Aumenta el index para borrar la colision temporal
	}
	
}

void Weapon::SavePlayerInfo(int index, Hands* playerH, Health* healthAux, Wallet* walletAux)
{
	playerInfo_[index].isNear = true;
	playerInfo_[index].playerHands = playerH;
	if (healthAux) playerInfo_[index].playerHealth = healthAux;
	else playerInfo_[index].playerWallet = walletAux;
}
void Weapon::DeletePlayerInfo(int index)
{
	playerInfo_[index].isNear = false;
	playerInfo_[index].playerHands = nullptr;
}

void Weapon::detectPlayer(Entity* playerDetected, int id)
{
	if (weaponType_ == WeaponID::Slipper) {
		cout << "Enemigo en rango" << endl;
		EnemyData newEnemy;
		newEnemy.enemy = playerDetected;
		newEnemy.id = id;
		playersInsideRange_.push_back(newEnemy);
	}
}

void Weapon::loseContactPlayer(Entity* playerDetected, int id) {
	if (weaponType_==WeaponID::Slipper && playersInsideRange_.size() > 0) {	//Salta error ya que el vector está vacio
		vector<EnemyData>::iterator it = playersInsideRange_.begin();
		while (it->id != id && it->enemy != playerDetected && it != playersInsideRange_.end()) {
			++it;
		}
		if (it != playersInsideRange_.end()) { 
			playersInsideRange_.erase(it);
			cout << "Enemigo salio del rango" << endl;
		};
	}
}

int Weapon::getPlayerId() {
	return currentHand_->getPlayerId();
}