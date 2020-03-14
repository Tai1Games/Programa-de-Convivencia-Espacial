#include "AttachesToObjects.h"
#include "InputHandler.h"

void AttachesToObjects::init() {
	mainCollider_ = GETCMP1_(Collider); //Obtiene el collider del cuerpo principal.
	mainCollider_->setUserData(this);
}

void AttachesToObjects::attachToObject() {
	b2WeldJointDef jointDef; //Definición del nuevo joint.
	jointDef.bodyA = mainCollider_->getBody(); //Body del jugador.
	jointDef.bodyB = bodyToBeAttached; //Body del objeto al que se tiene que atar.
	jointDef.collideConnected = false; //Flag que decide si estos 2 objetos van a ejercer físicas el uno contra el otro.
	jointDef.localAnchorA = jointDef.bodyA->GetLocalPoint(collPoint_);
	jointDef.localAnchorB = jointDef.bodyB->GetLocalPoint(collPoint_);
	jointDef.referenceAngle = jointDef.bodyB->GetAngle() - jointDef.bodyA->GetAngle();
	b2World* world = mainCollider_->getWorld();
	joint_ = (b2WeldJoint*)world->CreateJoint(&jointDef); //Crea el joint con la definición que hemos creado previamente
}

void AttachesToObjects::deAttachFromObject() {
	if (joint_ != nullptr) { //Destruye el joint. Si haces un delete(joint) peta por algún motivo. CREO que esto no deja basura.
		mainCollider_->getWorld()->DestroyJoint(joint_);
		joint_ = nullptr;
		bodyToBeAttached = nullptr;
	}
}

bool AttachesToObjects::isPressingInput() {
	InputHandler* ih = SDL_Game::instance()->getInputHandler();
	return (ih->isButtonDown(playerNumber_, SDL_CONTROLLER_BUTTON_A) && bodyToBeAttached == nullptr);
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
	cout << mainCollider_->getPos().x << "  " << mainCollider_->getPos().y << endl;
}