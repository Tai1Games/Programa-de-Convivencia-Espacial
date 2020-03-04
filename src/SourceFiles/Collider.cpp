#include "Collider.h"

Collider::Collider(b2World* world, b2BodyType type, float x, float y, float width, float height,
	float density, float friction, float restitution, int groupIndex, bool sensor) :
	world_(world),
	Component(ComponentType::Collider)
{
    width_[0] = width;
	height_[0] = height;
	bodyDef_.type = type;
	bodyDef_.position.Set(x, y);
	body_ = world_->CreateBody(&bodyDef_);
	shape_[0].SetAsBox(width, height);
	fixtureDef_[0].shape = &shape_[0];
	fixtureDef_[0].density = density;
	fixtureDef_[0].friction = friction;
	fixtureDef_[0].restitution = fmod(restitution, 1.0);
	fixtureDef_[0].filter.groupIndex = groupIndex;
	fixtureDef_[0].isSensor = sensor;
	body_->CreateFixture(&fixtureDef_[0]);
}

void Collider::createFixture(float width, float height, float density,
	float friction, float restitution, int groupIndex, bool sensor) {
	width_[1] = width;
	height_[1] = height;
	shape_[1].SetAsBox(width, height);
	fixtureDef_[1].shape = &shape_[1];
	fixtureDef_[1].density = density;
	fixtureDef_[1].friction = friction;
	fixtureDef_[1].restitution = fmod(restitution, 1.0);
	fixtureDef_[1].filter.groupIndex = groupIndex;
	fixtureDef_[1].isSensor = sensor;
	body_->CreateFixture(&fixtureDef_[1]);
}