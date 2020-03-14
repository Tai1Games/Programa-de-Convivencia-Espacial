#include "AttachesToObjects.h"
#include "InputHandler.h"

void AttachesToObjects::init() {
	mainCollider_ = GETCMP1_(Collider); //Obtiene el collider del cuerpo principal.
	mainCollider_->setUserData(this);
}

void AttachesToObjects::attachToObject() {
	b2WeldJointDef jointDef; //Definición del nuevo joint.
	jointDef.bodyA = bodyToBeAttached; //Body del objeto al que se tiene que atar.
	jointDef.bodyB = mainCollider_->getBody(); //Body del jugador.
	jointDef.collideConnected = true; //Flag que decide si estos 2 objetos van a ejercer físicas el uno contra el otro.
	jointDef.localAnchorA = collPoint_; //Punto en el que se crea el joint en referencia al JUGADOR. Esto queda por revisar una vez esté implementado el collider fancy de Álvar.

	b2World* world = mainCollider_->getWorld();
	joint_ = (b2WeldJoint*)world->CreateJoint(&jointDef); //Crea el joint con la definición que hemos creado previamente
}

void AttachesToObjects::deAttachFromObject() {
	if (joint_ != nullptr) { //Destruye el joint. Si haces un delete(joint) peta por algún motivo. CREO que esto no deja basura.
		mainCollider_->getWorld()->DestroyJoint(joint_);
		joint_ = nullptr;
	}
}

bool AttachesToObjects::isPressingInput() {
	InputHandler* ih = SDL_Game::instance()->getInputHandler();

	return (ih->isButtonJustDown(playerNumber_, SDL_CONTROLLER_BUTTON_A));
}

void AttachesToObjects::handleInput() {
	InputHandler* ih = SDL_Game::instance()->getInputHandler();

	if (ih->isButtonJustUp(playerNumber_, SDL_CONTROLLER_BUTTON_A)) {
		deAttachFromObject();
	}
}

void AttachesToObjects::registerCollision(b2Body* attachableObject, b2Vec2 collPoint) {
	bodyToBeAttached = attachableObject;
	collPoint_ = collPoint;
	registeredCollision = true;
}

void AttachesToObjects::update() {
	if (registeredCollision) {
		registeredCollision = false;
		attachToObject();
	}
}