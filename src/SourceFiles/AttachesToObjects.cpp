#include "AttachesToObjects.h"

void AttachesToObjects::init() {
	mainCollider = GETCMP1_(Collider); //Obtiene el collider del cuerpo principal.
}

void AttachesToObjects::attachToObject(Collider* attachableObject, b2Vec2 collPoint) {
	b2WeldJointDef jointDef; //Definición del nuevo joint.
	jointDef.bodyA = mainCollider->getBody(); //Body del jugador.
	jointDef.bodyB = attachableObject->getBody(); //Body del objeto al que se tiene que atar.
	jointDef.collideConnected = true; //Flag que decide si estos 2 objetos van a ejercer físicas el uno contra el otro.
	jointDef.localAnchorA = collPoint; //Punto en el que se crea el joint en referencia al JUGADOR. Esto queda por revisar una vez esté implementado el collider fancy de Álvar.

	joint = (b2WeldJoint*)mainCollider->getWorld()->CreateJoint(&jointDef); //Crea el joint con la definición que hemos creado previamente
}

void AttachesToObjects::deAttachFromObject() {
	if (joint != nullptr) { //Destruye el joint. Si haces un delete(joint) peta por algún motivo. CREO que esto no deja basura.
		mainCollider->getWorld()->DestroyJoint(joint);
	}
}