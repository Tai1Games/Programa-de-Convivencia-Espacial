#include "Collider.h"

Collider::Collider(b2World* world, b2BodyType type, float x, float y, float width, float height,
	float density, float friction, bool sensor) : world_(world),
	Component(ComponentType::Collider) {
	bodyDef_.type = type;
	bodyDef_.position.Set(x, y);
	body_ = world_->CreateBody(&bodyDef_);
	shape_.SetAsBox(width, height);
	fixtureDef_.shape = &shape_;
	fixtureDef_.density = density;
	fixtureDef_.friction = friction;
	fixtureDef_.isSensor = sensor;
	body_->CreateFixture(&fixtureDef_);
}