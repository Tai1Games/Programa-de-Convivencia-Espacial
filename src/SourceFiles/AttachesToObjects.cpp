#include "AttachesToObjects.h"

void AttachesToObjects::init() {
	mainCollider = GETCMP1_(Collider);
}

void AttachesToObjects::attachToObject(Collider* attachableObject) {
	b2WeldJointDef jointDef;
	jointDef.bodyA = mainCollider->getBody();
	jointDef.bodyB = attachableObject->getBody();
	jointDef.collideConnected = false;
}

void AttachesToObjects::update() {

}