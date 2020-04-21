#include "MeleeWeapon.h"
#include "Hands.h"
#include "Entity.h"
#include "Collision.h"

MeleeWeapon::MeleeWeapon(WeaponID wId, int dmg, int impactDmg, int cooldownFrames) : ActionableWeapon(ComponentType::MeleeWeapon, wId, impactDamage_, cooldownFrames),
damage_(dmg) {};

void MeleeWeapon::init() {
	Weapon::init();
	//Fixture Sensor añadido por el componente
	mainCollider_->createRectangularFixture(mainCollider_->getW(0) * 4, mainCollider_->getH(0) * 4, 1, 0.1, 0, Collider::CollisionLayer::PickableObject, true);
	//Pone la informacion de esta clase en el body, para poder usarla en el Listener
}

void MeleeWeapon::action() {
	if (!beenActivated_) {
		cout << "ACCION ARMA MELEE ACTIVADA" << endl;
		if (playersInsideRange_.size() > 0) {
			//Calculo del daño de la chancla
			if (playerInfo_[currentHand_->getPlayerId()].playerHealth) {
				damage_ = playerInfo_[currentHand_->getPlayerId()].playerHealth->getHealthMax() - playerInfo_[currentHand_->getPlayerId()].playerHealth->getHealth() + 1;
			}
			else damage_ = calculateCoinsDropped(playerInfo_[currentHand_->getPlayerId()].playerWallet->getCoins());

			//cout << "Golpeaste con una fuerza de " << damage_ << " al contrincante" << endl;
			vector<EnemyData>::iterator it = playersInsideRange_.begin();
			while (it != playersInsideRange_.end()) {

				//Patear al enemigo
				Health* auxHe = it->enemy->getComponent<Health>(ComponentType::Health);
				Wallet* auxWa = it->enemy->getComponent<Wallet>(ComponentType::Wallet);

				Collider* auxCo = it->enemy->getComponent<Collider>(ComponentType::Collider);

				b2Vec2 knockback = auxCo->getPos() - mainCollider_->getPos();
				knockback.Normalize();
				knockback *= CONST(double, "WEAPON_MELEE_KNOCKBACK");

				auxCo->applyLinearImpulse(knockback, b2Vec2(0, 1));
				if (auxHe) auxHe->subtractLife(damage_);
				else auxWa->dropCoins(damage_, it->enemy->getComponent<PlayerData>(ComponentType::PlayerData)->getPlayerNumber());

				++it;
			}

			//Tras aplicar el golpe a tol que estén en rango limpiamos el vector
			playersInsideRange_.clear();
		}
		beenActivated_ = true;
	}
	else
		cout << "COOLDING DOWN" << endl;
}

void MeleeWeapon::PickObjectBy(Hands* playerHands) {
	if (playerHands->getWeaponID() == NoWeapon) {
		currentHand_ = playerHands;
		picked_ = true;
		currentHand_->setWeapon(weaponType_, this);
		//Creamos el trigger de ataque
		mainCollider_->createRectangularFixture(mainCollider_->getW(0) * 2, mainCollider_->getH(0) * 2, 1, 0.1, 0, Collider::CollisionLayer::PickableObject, true);
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
		vw_->setDrawable(false);
	}
}

void MeleeWeapon::UnPickObject() {
	//Trigger de la Chancla(Restairamos sus capas de colision)
	b2Filter aux1 = mainCollider_->getFixture(0)->GetFilterData();
	aux1.categoryBits = Collider::CollisionLayer::PickableObject;
	aux1.maskBits = Collider::CollisionLayer::Player | Collider::CollisionLayer::Wall;
	mainCollider_->getFixture(1)->SetFilterData(aux1);
	//Caja colision de la chancla
	b2Filter aux = mainCollider_->getFixture(0)->GetFilterData();
	aux.categoryBits = Collider::CollisionLayer::NormalObject;
	aux.maskBits = Collider::CollisionLayer::NormalObject | Collider::CollisionLayer::NormalAttachableObject | Collider::CollisionLayer::Player | Collider::CollisionLayer::Wall;
	mainCollider_->getFixture(0)->SetFilterData(aux);
	//Destruimos el trigger de ataque
	mainCollider_->destroyFixture(index);
	//index++;	//Aumenta el index para borrar la colision temporal

	Weapon::UnPickObject();
}

void MeleeWeapon::detectPlayer(Entity* playerDetected, int id)
{
	cout << "Enemigo en rango" << endl;
	EnemyData newEnemy;
	newEnemy.enemy = playerDetected;
	newEnemy.id = id;
	playersInsideRange_.push_back(newEnemy);
}

void MeleeWeapon::loseContactPlayer(Entity* playerDetected, int id) {
	if (playersInsideRange_.size() > 0) {	//Salta error ya que el vector está vacio
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