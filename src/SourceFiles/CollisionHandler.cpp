#include "CollisionHandler.h"
#include "RouterLogic.h"
#include "StocksGameMode.h"
//This method calculates the damage recieved by the impact of an object (or another player) with the player

void CollisionHandler::damageOnImpact(b2Fixture* fix, b2Fixture* player, Health* playerHealth) {
	//Measure de impact of an object with the player
	b2Vec2 force = fix->GetBody()->GetMass() * fix->GetBody()->GetLinearVelocity();

	int impact = force.Length();

	//Depending on the force of impact we apply damage to the player
	if (impact >= CONST(int, "LOW_DAMAGE")&& CONST(double, "MEDIUM_DAMAGE")) {playerHealth->subtractLife(1); }

	if (impact >= CONST(double, "MEDIUM_DAMAGE") && impact < CONST(double, "HIGH_DAMAGE")) {playerHealth->subtractLife(2);}

	if (impact >= CONST(double, "HIGH_DAMAGE")) {playerHealth->subtractLife(3);}

	if (playerHealth->getHealth() <= 0)
	{
		//reset player

		//soltar objetos agarrados
		AttachesToObjects* a = static_cast<AttachesToObjects*>(static_cast<Entity*>(player->GetBody()->GetUserData())->getComponent<AttachesToObjects>(ComponentType::AttachesToObjects));
		if (a != nullptr && a->isAttached()) vecAttach.push_back(a);
		//soltar arma
		Hands* h = static_cast<Hands*>(static_cast<Entity*>(player->GetBody()->GetUserData())->getComponent<Hands>(ComponentType::Hands));
		Weapon* w = nullptr;
		if (h != nullptr) w = h->getWeapon();
		if (w != nullptr) vecWeapon.push_back(w);
		//respawn
		StocksGameMode* s = nullptr;
		bool stocks = (s = dynamic_cast<StocksGameMode*>(gMode_));
		PlayerData* p = static_cast<PlayerData*>(static_cast<Entity*>(player->GetBody()->GetUserData())->getComponent<PlayerData>(ComponentType::PlayerData));
		moveData m;
		m.body = player->GetBody();
		m.pos = b2Vec2(tilemap_->getPlayerSpawnPoint(p->getPlayerNumber()).x, tilemap_->getPlayerSpawnPoint(p->getPlayerNumber()).y); //punto de respawn provisional
		if (stocks && s->onPlayerDead(p->getPlayerNumber())|| !stocks) {	//si le quedan vidas
			playerHealth->resetHealth();
		}
		else if(stocks) {	//si no le quedan vidas le mandamos lejos provisionalmente
			m.pos = b2Vec2((1+p->getPlayerNumber())* 50, 0);
		}
		vecMove.push_back(m);

		//cuerpo muerto
		bodyData body;
		body.pos = player->GetBody()->GetPosition();
		body.angle = player->GetBody()->GetAngle();
		vecBody.push_back(body);
	}
}

//Handles start of collisions
void CollisionHandler::BeginContact(b2Contact* contact)
{
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();
	Health* player_Health = nullptr;
	AttachesToObjects* player_AttachesToObjects = nullptr;
	Weapon* pickableObj = nullptr;
	Hands* playerHands = nullptr;
	RouterLogic* routerLogic = nullptr;
	Collider* playerCollider = nullptr;
	PlayerData* playerData = nullptr;

	if (fixA->GetFilterData().categoryBits == Collider::CollisionLayer::Wall && fixB->GetFilterData().categoryBits == Collider::CollisionLayer::Player ||
		fixB->GetFilterData().categoryBits == Collider::CollisionLayer::Wall && fixA->GetFilterData().categoryBits == Collider::CollisionLayer::Player) {

	}
	//Comprueba que FixA es el jugador, que FixB es un trigger, que el jugador está presionando la tecla A (mando) o Space (teclado) y que no está agarrado a nada más.
	if (AttachableObjectCollidesWithPlayer(fixA, player_AttachesToObjects) && (fixB->GetFilterData().categoryBits == Collider::CollisionLayer::NormalAttachableObject || fixB->GetFilterData().categoryBits == Collider::Wall) && player_AttachesToObjects->canAttachToObject()) {
		b2WorldManifold manifold; //Una manifold es un registro donde se guardan todas las colisiones
		contact->GetWorldManifold(&manifold); //Obtenemos la manifold global
		weldData newWeld; //Struct donde guardamos los datos necesarios para crear un weld
		newWeld.player = player_AttachesToObjects;
		newWeld.bodyToBeAttached = fixB->GetBody();
		newWeld.collPoint = b2Vec2(manifold.points[0].x, manifold.points[0].y); //Punto de colisi�n. En cualquier colisi�n siempre hay 2 puntos de colisi�n. Con 1 nos basta.
		vecWeld.push_back(newWeld); //Metemos el weldData en el vector. La raz�n por la que no hacemos el joint ya es porque no se puede crear un joint en medio de un step.
	}
	else if (fixB->GetFilterData().categoryBits) {
		//check collision then do whatever, in this case twice because it might be two players colliding
		if (ObjectCollidesWithPlayer(fixA, player_Health) && !fixB->IsSensor()) {
			damageOnImpact(fixB, fixA, player_Health);	//Check the stats of the other object
		}

		player_Health = nullptr;	//Lo reseteamos para evitar problemas

		if (ObjectCollidesWithPlayer(fixB, player_Health) && !fixA->IsSensor()) {
			damageOnImpact(fixA, fixB, player_Health);	//Check the stats of the other object
		}
	}
	//Melee Weapons collisions
	
	if(contact->GetFixtureB()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon && contact->GetFixtureB()->IsSensor()
	&& contact->GetFixtureA()->GetFilterData().categoryBits == Collider::CollisionLayer::Player)
	{
		Entity* aux = static_cast<Entity*>(fixB->GetBody()->GetUserData());
		Entity* aux2 = static_cast<Entity*>(fixA->GetBody()->GetUserData());

		Weapon* weAux = aux->getComponent<Weapon>(ComponentType::Weapon);
		Hands* haAux = aux2->getComponent<Hands>(ComponentType::Hands);

		player_Health = nullptr;	//Lo reseteamos para evitar problemas

		ObjectCollidesWithPlayer(contact->GetFixtureA(), player_Health);

		if(weAux->getCurrentHand() != nullptr && player_Health != nullptr && (weAux->getCurrentHand() != haAux)) {
			weAux->detectPlayer(aux2, aux2->getComponent<PlayerData>(ComponentType::PlayerData)->getId());
			//cout << "Golpeaste al objetivo" << endl;
		}
	}
	else if (contact->GetFixtureA()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon && contact->GetFixtureA()->IsSensor()
		&& contact->GetFixtureB()->GetFilterData().categoryBits == Collider::CollisionLayer::Player){
		
		Entity* aux = static_cast<Entity*>(fixA->GetBody()->GetUserData());
		Entity* aux2 = static_cast<Entity*>(fixB->GetBody()->GetUserData());

		Weapon* weAux = aux->getComponent<Weapon>(ComponentType::Weapon);
		Hands* haAux = aux2->getComponent<Hands>(ComponentType::Hands);
		
		player_Health = nullptr;	//Lo reseteamos para evitar problemas

		ObjectCollidesWithPlayer(contact->GetFixtureB(), player_Health);
		
		if (weAux->getCurrentHand() != nullptr && player_Health != nullptr && (weAux->getCurrentHand() != haAux)) {
		
			weAux->detectPlayer(aux2, aux2->getComponent<PlayerData>(ComponentType::PlayerData)->getId());

			//cout << "Golpeaste al objetivo" << endl;
		}
	}
	player_Health = nullptr;

	//Pickable weapon collisions
	if ((contact->GetFixtureA()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon ||
		contact->GetFixtureB()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon) &&
		PlayerCanPickWeapon(contact, pickableObj, playerHands)) {
		cout << "Pickeable weapon" << endl;

		player_Health = nullptr;
		ObjectCollidesWithPlayer(fixA, player_Health);
		if (player_Health != nullptr) {
			pickableObj->SavePlayerInfo(playerHands->getPlayerId(), playerHands, player_Health);
			
		}
		player_Health = nullptr;

		ObjectCollidesWithPlayer(fixB, player_Health);
		if(player_Health != nullptr) {
			pickableObj->SavePlayerInfo(playerHands->getPlayerId(), playerHands, player_Health);
			
		}
	}

	if (contact->GetFixtureA()->GetFilterData().categoryBits == Collider::CollisionLayer::Trigger || //Colisiones entre Triggers y otros objetos
		contact->GetFixtureB()->GetFilterData().categoryBits == Collider::CollisionLayer::Trigger) {
		if (PlayerCollidesWithRouterArea(contact, routerLogic, playerCollider, playerData)) {
			routerLogic->detectPlayer(playerCollider, playerData->getPlayerNumber());
		}
	}
}

//Handles end of collisions
void CollisionHandler::EndContact(b2Contact* contact) {
	//Pickable weapons
	Weapon* pickableObj = nullptr;
	Hands* playerHands = nullptr;
	if ((contact->GetFixtureA()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon ||
		contact->GetFixtureB()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon) &&
		PlayerCanPickWeapon(contact, pickableObj, playerHands)) {
		pickableObj->DeletePlayerInfo(playerHands->getPlayerId());
		cout << "Weapon out of reach" << endl;
	}

	RouterLogic* routerLogic = nullptr;
	PlayerData* playerData = nullptr;
	Collider* playerCollider = nullptr;

	if (contact->GetFixtureA()->GetFilterData().categoryBits == Collider::CollisionLayer::Trigger || //Colisiones entre Triggers y otros objetos
		contact->GetFixtureB()->GetFilterData().categoryBits == Collider::CollisionLayer::Trigger) {
		if (PlayerCollidesWithRouterArea(contact, routerLogic, playerCollider, playerData)) {
			routerLogic->loseContactPlayer(playerCollider, playerData->getId());
		}
	}
	//Out of melee weapon trigger
	if (contact->GetFixtureA()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon ||
		contact->GetFixtureB()->GetFilterData().categoryBits == Collider::CollisionLayer::Weapon) {
		
		exitChanclaTrigger(contact);
	}
}

//If you want to disable a collision after it's detected
void CollisionHandler::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

//Gather info about impulses
void CollisionHandler::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}

//to add a new collision behaviour, make a method that checks if it's the specific collision you want
//you can distinguish bodies by their user data or make them collide with certain objects only with collision layers
//if you need to use a component you have to do collider->setUserData(this) in the component's init first
bool CollisionHandler::ObjectCollidesWithPlayer(b2Fixture* fixA, Health*& player)
{
	//Obtenemos los datos guardados en el Collider
	Entity* aux = static_cast<Entity*>(fixA->GetBody()->GetUserData());

	if (aux != nullptr) {		//Cuidado de que no sea null

	//Cogemos el health si es que lo tiene
		player = aux->getComponent<Health>(ComponentType::Health);
	}

	if (player != nullptr) {	//Si lo tiene es que es un player
		return true;
	}
	else return false;
}

bool CollisionHandler::PlayerCanPickWeapon(b2Contact* contact, Weapon*& pickableObj, Hands*& player) {
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
		fixAentity->hasComponent(ComponentType::Hands)) {

		player = static_cast<Hands*>(fixAentity->getComponent<Hands>(ComponentType::Hands));
		return true;
	}
	return false;
}

bool CollisionHandler::AttachableObjectCollidesWithPlayer(b2Fixture* fixA, AttachesToObjects*& player) {
	return (player = static_cast<AttachesToObjects*>(static_cast<Entity*>(fixA->GetBody()->GetUserData())->getComponent<AttachesToObjects>(ComponentType::AttachesToObjects)));
}

//Checks if one fixture belongs to a Player (PlayerData and Collider component) and if the other fixture belongs to a Router (RouterLogic component)
bool CollisionHandler::PlayerCollidesWithRouterArea(b2Contact* contact, RouterLogic*& router, Collider*& collPlayer, PlayerData*& playerData) {
	Entity* fixAentity = static_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Entity* fixBentity = static_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());

	if (fixAentity->hasComponent(ComponentType::RouterLogic) && fixBentity->hasComponent(ComponentType::Collider) && fixBentity->hasComponent(ComponentType::PlayerData)) {
		router = static_cast<RouterLogic*>(fixAentity->getComponent<RouterLogic>(ComponentType::RouterLogic));
		playerData = static_cast<PlayerData*>(fixBentity->getComponent<PlayerData>(ComponentType::PlayerData));
		collPlayer = static_cast<Collider*>(fixBentity->getComponent<Collider>(ComponentType::Collider));

		return true;
	}

	else if (fixBentity->hasComponent(ComponentType::RouterLogic) && fixAentity->hasComponent(ComponentType::Collider) && fixAentity->hasComponent(ComponentType::PlayerData)) {
		router = static_cast<RouterLogic*>(fixBentity->getComponent<RouterLogic>(ComponentType::RouterLogic));
		playerData = static_cast<PlayerData*>(fixAentity->getComponent<PlayerData>(ComponentType::PlayerData));
		collPlayer = static_cast<Collider*>(fixAentity->getComponent<Collider>(ComponentType::Collider));

		return true;
	}

	return false;
}

void CollisionHandler::exitChanclaTrigger(b2Contact* contact) {
	Entity* fixAentity = static_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Entity* fixBentity = static_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());

	if (fixAentity->hasComponent(ComponentType::Health)) {
		if (fixBentity->hasComponent(ComponentType::Weapon) && fixAentity->hasComponent(ComponentType::PlayerData)) {
			
			fixBentity->getComponent<Weapon>(ComponentType::Weapon)->loseContactPlayer(fixAentity, fixAentity->getComponent<PlayerData>(ComponentType::PlayerData)->getId());

		}
	}
	else if (fixBentity->hasComponent(ComponentType::Health)) {
		if (fixAentity->hasComponent(ComponentType::Weapon) && fixBentity->hasComponent(ComponentType::PlayerData)) {
			
			fixAentity->getComponent<Weapon>(ComponentType::Weapon)->loseContactPlayer(fixBentity, fixBentity->getComponent<PlayerData>(ComponentType::PlayerData)->getId());

		}
	}
}

void CollisionHandler::SolveInteractions() {
	for (int k = 0; k < vecWeld.size(); k++) { //Recorre el vector resolviendo todos los joint y lo limpia al final.
		vecWeld[k].player->attachToObject(vecWeld[k].bodyToBeAttached, vecWeld[k].collPoint);
	}
	vecWeld.clear();
	for (int k = 0; k < vecMove.size(); k++) { //Recorre el vector resolviendo todos los move y lo limpia al final.
		vecMove[k].body->SetTransform(vecMove[k].pos, 0);
		vecMove[k].body->SetLinearVelocity(b2Vec2_zero);
		vecMove[k].body->SetAngularVelocity(0);
	}
	vecMove.clear();
	for (int k = 0; k < vecWeapon.size(); k++) { //Recorre el vector soltando los weapon y lo limpia al final.
		vecWeapon[k]->UnPickObject();
	}
	vecWeapon.clear();
	for (int k = 0; k < vecAttach.size(); k++) { //Recorre el vector soltando los agarres y lo limpia al final.
		vecAttach[k]->deAttachFromObject();
	}
	vecAttach.clear();
}
