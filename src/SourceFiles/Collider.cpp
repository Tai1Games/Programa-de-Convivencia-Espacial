#include "Collider.h"

Collider::Collider(b2World* world, b2BodyType type, float x, float y, float width, float height,

	float density, float friction, float restitution, float linearDrag, float angDrag, CollisionLayer c, bool sensor) :

	world_(world),
	Component(ComponentType::Collider)
{
	bodyDef_.type = type;
	bodyDef_.position.Set(x, y);
	bodyDef_.linearDamping = linearDrag;
	bodyDef_.angularDamping = angDrag;
	body_ = world_->CreateBody(&bodyDef_);

	createFixture(width, height, density, friction, restitution, c, sensor);
}

void Collider::createFixture(float width, float height, float density,
	float friction, float restitution, CollisionLayer c, bool sensor) {
	widths_.push_back(width);
	heights_.push_back(height);
	b2PolygonShape shape;
	shape.SetAsBox(width, height);
	shapes_.push_back(shape);
	b2FixtureDef aux;
	aux.shape = &shapes_.back();
	aux.density = density;
	aux.friction = friction;
	aux.restitution = fmod(restitution, 1.0);

	aux.filter.categoryBits = c; //What am i?
	switch (c) {
	case NormalObject:
		aux.filter.maskBits = NormalObject | NormalAttachableObject | Player | Wall; //what do I collide with?
		break;
	case NormalAttachableObject:
		aux.filter.maskBits = NormalObject | NormalAttachableObject | Player | Wall; //what do I collide with?
		break;
	case Player:
		aux.filter.maskBits = NormalObject | NormalAttachableObject | Player | Trigger | Weapon | Wall;
		break;
	case Trigger:
		aux.filter.maskBits = Player;
		break;
	case Weapon:
		aux.filter.maskBits = Player | Wall;
		break;
	case UnInteractableObject:
		aux.filter.maskBits = Wall;
		break;
	case Wall:
		aux.filter.maskBits = UnInteractableObject;
		break;
	}
	aux.isSensor = sensor;
	fixtureDefs_.push_back(aux);
	fixtures_.push_back(body_->CreateFixture(&fixtureDefs_.back()));
}

void Collider::destroyFixture(int i) {
	body_->DestroyFixture(fixtures_[i]);
	/*fixtures_.erase(fixtures_.begin() + i);
	fixtureDef_.erase(fixtureDef_.begin() + i);
	shape_.erase(shape_.begin() + i);*/

}
