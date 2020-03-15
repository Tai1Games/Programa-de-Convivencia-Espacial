#include "CollisionHandler.h"

//Handles start of collisions
void CollisionHandler::BeginContact(b2Contact* contact)
{
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();
	//player damage collision
	Health* player_Health = nullptr;
	AttachesToObjects* player_AttachesToObjects = nullptr;
	Weapon* pickableObj = nullptr;
	Hands* playerHands = nullptr;

	if (AttachableObjectCollidesWithPlayer(fixA, player_AttachesToObjects) && fixB->GetFilterData().categoryBits == Collider::CollisionLayer::Trigger) { //Comprueba que FixA es el jugador y que FixB es un Trigger
		if (player_AttachesToObjects->canAttachToObject()) { //Comprueba que el jugador puede agarrarse al objeto (está pulsando la A y no está agarrado a ningun otro)
			b2WorldManifold manifold; //Una manifold es un registro donde se guardan todas las colisiones
			contact->GetWorldManifold(&manifold); //Obtenemos la manifold global
			weldData newWeld; //Struct donde guardamos los datos necesarios para crear un weld
			newWeld.player = player_AttachesToObjects;
			newWeld.bodyToBeAttached = fixB->GetBody();
			newWeld.collPoint = b2Vec2(manifold.points[0].x, manifold.points[0].y); //Punto de colisión. En cualquier colisión siempre hay 2 puntos de colisión. Con 1 nos basta.
			vecWeld.push_back(newWeld); //Metemos el weldData en el vector. La razón por la que no hacemos el joint ya es porque no se puede crear un joint en medio de un step.
		}
	}

	if ((contact->GetFixtureA()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon ||
		contact->GetFixtureB()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon) &&
		PlayerCanPickWeapon(contact, pickableObj, playerHands)) {
		cout << "jaja si" << endl;
		pickableObj->SavePlayerInfo(playerHands->getPlayerId(), playerHands);
	}


	else {
		//player damage collision
		Health* playerHealth = nullptr;

		//check collision then do whatever, in this case twice because it might be two players colliding
		if (ObjectCollidesWithPlayer(fixA, playerHealth) && fixB->GetFilterData().categoryBits == Collider::CollisionLayer::Normal) {
			playerHealth->subtractLife(1);
			std::cout << "Health: " << playerHealth->getHealth() << endl;
		}
		if (ObjectCollidesWithPlayer(fixB, playerHealth) && fixB->GetFilterData().categoryBits == Collider::CollisionLayer::Normal) {
			playerHealth->subtractLife(1);
			std::cout << "Health: " << playerHealth->getHealth() << endl;
		}
		

	}	
}

//Handles end of collisions
void CollisionHandler::EndContact(b2Contact* contact)
{
	//Pickable weapons
	Weapon* pickableObj = nullptr;
	Hands* playerHands = nullptr;
	if ((contact->GetFixtureA()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon ||
		contact->GetFixtureB()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon) &&
		PlayerCanPickWeapon(contact, pickableObj, playerHands)) {
		pickableObj->DeletePlayerInfo(playerHands->getPlayerId());
		cout << "jaja no" << endl;
	}

}

//If you want to disable a collision after it's detected
void CollisionHandler::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

//Gather info about impulses
void CollisionHandler::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}

//to add a new collision behaviour, make a method that checks if it's the specific collision you want
//you can distinguish bodies by their user data or make them collide with certain objects only with collision layers
//if you need to use a component you have to do collider->setUserData(this) in the component's init first
bool CollisionHandler::ObjectCollidesWithPlayer(b2Fixture* fixA, Health* &player)
{
	Entity* fixAEnt = static_cast<Entity*>(fixA->GetBody()->GetUserData());
	if ((fixAEnt->hasComponent(ComponentType::Health)) &&
		(player = static_cast<Health*>(fixAEnt->getComponent<Health>(ComponentType::Health)))) return true;
	else return false;
}

bool CollisionHandler::PlayerCanPickWeapon(b2Contact* contact, Weapon* &pickableObj, Hands* &player) {
	Entity* fixAentity = static_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Entity* fixBentity = static_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());

	if ((fixAentity->hasComponent(ComponentType::Weapon)) &&
		(pickableObj = static_cast<Weapon*>(fixAentity->getComponent<Weapon>(ComponentType::Weapon))) &&
		fixBentity->hasComponent(ComponentType::Hands)) {

		player = static_cast<Hands*>(fixBentity->getComponent<Hands>(ComponentType::Hands));
		return true;
	}
	else if ((fixBentity->hasComponent(ComponentType::Weapon)) &&
		(pickableObj = static_cast<Weapon*>(fixBentity->getComponent<Weapon>(ComponentType::Weapon))) &&
		fixAentity->hasComponent(ComponentType::Hands)){

		player = static_cast<Hands*>(fixAentity->getComponent<Hands>(ComponentType::Hands));
		return true;
	}
	return false;
}

bool CollisionHandler::AttachableObjectCollidesWithPlayer(b2Fixture* fixA, AttachesToObjects*& player) {
	return (player = static_cast<AttachesToObjects*>(static_cast<Entity*>(fixA->GetBody()->GetUserData())->getComponent<AttachesToObjects>(ComponentType::AttachesToObjects)));
}

void CollisionHandler::SolveInteractions() {
	for (int k = 0; k < vecWeld.size(); k++) { //Recorre el vector resolviendo todos los joint y lo limpia al final.
		vecWeld[k].player->attachToObject(vecWeld[k].bodyToBeAttached, vecWeld[k].collPoint);
	}
	vecWeld.clear();
}
