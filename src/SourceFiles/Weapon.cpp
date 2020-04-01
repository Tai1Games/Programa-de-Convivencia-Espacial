#include "Weapon.h"
#include <iostream>
#include "InputHandler.h"
#include "Hands.h"
#include "Health.h"

void Weapon::init()
{
	ih_ = SDL_Game::instance()->getInputHandler();
	mainCollider_ = GETCMP1_(Collider);
	vw_ = GETCMP1_(Viewer);
	//Fixture Sensor a�adido por el componente
	mainCollider_->createRectangularFixture(mainCollider_->getW(0)*4, mainCollider_->getH(0)*4, 1, 0.1, 0, Collider::CollisionLayer::Weapon, true);
	//Pone la informacion de esta clase en el body, para poder usarla en el Listener
	//Tama�o del vector segun el numero de jugadores
	playerInfo_.resize(ih_->getNumControllers());
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
			//else { vw_->setDrawable(true); }
		}
		//else { vw_->setDrawable(false); }
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
		coolDown = false;
		UnPickObject();
	}
	else if (IsPicked() && ih_->isButtonJustDown(currentHand_->getPlayerId(), SDL_CONTROLLER_BUTTON_X) && !coolDown)
	{
		coolDown = true;
		Action();
		actionTime = 0;
	}
}

void Weapon::PickObjectBy(Hands* playerH)
{
	if (playerH->getWeaponID() == NoWeapon) {
		currentHand_ = playerH;
		picked_ = true;
		currentHand_->setWeapon(weaponType_, this);
		if (weaponType_ == WeaponID::Chancla) {
			mainCollider_->createRectangularFixture(mainCollider_->getW(0)*3, mainCollider_->getH(0)*2, 1, 0.1, 0, Collider::CollisionLayer::Weapon, true);
			//Trigger de la Chancla(Cambiamos con quien colisiona)
			b2Filter aux1 = mainCollider_->getFixture(0)->GetFilterData();
			aux1.categoryBits = Collider::CollisionLayer::Trigger;
			aux1.maskBits = Collider::CollisionLayer::Trigger;
			mainCollider_->getFixture(1)->SetFilterData(aux1);
			//Caja colision de la chancla
			b2Filter aux = mainCollider_->getFixture(0)->GetFilterData();
			aux.categoryBits = Collider::CollisionLayer::Weapon;
			aux.maskBits = Collider::CollisionLayer::Trigger;
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
	if (weaponType_ == WeaponID::Chancla) {
		mainCollider_->createRectangularFixture(mainCollider_->getW(0) * 4, mainCollider_->getH(0) * 4, 1, 0.1, 0, Collider::CollisionLayer::Weapon, true);
		//Trigger de la Chancla(Restairamos sus capas de colision)
		b2Filter aux1 = mainCollider_->getFixture(0)->GetFilterData();
		aux1.categoryBits = Collider::CollisionLayer::Weapon;
		aux1.maskBits = Collider::CollisionLayer::Trigger;
		mainCollider_->getFixture(1)->SetFilterData(aux1);
		//Caja colision de la chancla
		b2Filter aux = mainCollider_->getFixture(0)->GetFilterData();
		aux.categoryBits = Collider::CollisionLayer::NormalObject;
		aux.maskBits= Collider::CollisionLayer::NormalObject | Collider::CollisionLayer::NormalAttachableObject | Collider::CollisionLayer::Player;;
		mainCollider_->getFixture(0)->SetFilterData(aux);
	}
	mainCollider_->getBody()->SetEnabled(true);
	vw_->setDrawable(true);
	mainCollider_->setLinearVelocity(b2Vec2(0, 0));
	mainCollider_->setTransform(b2Vec2(currentHand_->getPos().x, currentHand_->getPos().y), currentHand_->getAngle());
	mainCollider_->applyLinearImpulse(b2Vec2(currentHand_->getDir().x * CONST(double, "WEAPON_THROW_SPEED"), -currentHand_->getDir().y * CONST(double, "WEAPON_THROW_SPEED")), mainCollider_->getBody()->GetLocalCenter());
	mainCollider_->getBody()->SetAngularVelocity(CONST(double, "WEAPON_SPIN_SPEED"));
	currentHand_ = nullptr;
}

void Weapon::SavePlayerInfo(int index, Hands* playerH, Health* healthAux)
{
	playerInfo_[index].isNear = true;
	playerInfo_[index].playerHands = playerH;
	playerInfo_[index].playerHealth = healthAux;
}
void Weapon::DeletePlayerInfo(int index)
{
	playerInfo_[index].isNear = false;
	playerInfo_[index].playerHands = nullptr;
}

void Weapon::detectPlayer(Entity* playerDetected, int id)
{
	EnemyData newEnemy;
	newEnemy.enemy= playerDetected;
	newEnemy.id = id;
	playersInsideRange_.push_back(newEnemy);
}

void Weapon::loseContactPlayer(Entity* playerDetected, int id) {
	vector<EnemyData>::iterator it = playersInsideRange_.begin();
	while (it->id != id && it->enemy != playerDetected && it != playersInsideRange_.end()) {
		++it;
	}
	if (it != playersInsideRange_.end()) playersInsideRange_.erase(it);
}

void Weapon::Action() {
	if (weaponType_ == WeaponID::Chancla) {
		//Calculo del daño de la chancla
		damage_ = playerInfo_[currentHand_->getPlayerId()].playerHealth->getHealthMax() - playerInfo_[currentHand_->getPlayerId()].playerHealth->getHealth() + 1;
		//cout << "Golpeaste con una fuerza de " << damage_ << " al contrincante" << endl;
		vector<EnemyData>::iterator it = playersInsideRange_.begin();
		while (it != playersInsideRange_.end()) {

			//Patear al enemigo
			Health* auxHe = it->enemy->getComponent<Health>(ComponentType::Health);
			Collider* auxCo = it->enemy->getComponent<Collider>(ComponentType::Collider);

			b2Vec2 knockback = auxCo->getPos() - mainCollider_->getPos();
			knockback.Normalize();
			knockback *= CONST(double, "WEAPON_MELEE_KNOCKBACK");

			auxCo->applyLinearImpulse(knockback, b2Vec2(0, 1));
			auxHe->subtractLife(damage_);


			++it;
		}
	}
}

int Weapon::getDamage() {
	return damage_;
}


bool Weapon::isOnHit(){
	return coolDown;
}

int Weapon::getPlayerId() {
	return currentHand_->getPlayerId();
}