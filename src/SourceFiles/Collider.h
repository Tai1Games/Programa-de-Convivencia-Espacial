#pragma once
#include "Component.h"
#include "box2d.h"

class Collider : public Component
{
public:
	Collider(b2World* world, b2BodyType type, float x, float y, float width, float height,
		float density, float friction, float restitution, bool sensor);
	~Collider() {
		world_->DestroyBody(body_); world_ = nullptr;
	}

	//getters
	float getW() { return width_; }
	float getH() { return height_; }
	b2Vec2 getPos() { return body_->GetPosition(); }
	b2Vec2 getLinearVelocity() { return body_->GetLinearVelocity(); }
	b2BodyType getType() { return body_->GetType(); }
	b2Transform getTransform() { return body_->GetTransform(); }
	float getAngle() { return body_->GetAngle(); }
	float getMass() { return body_->GetMass(); }
	bool isAwake() { return body_->IsAwake(); }
	bool isSensor() { return fixtureDef_.isSensor; }
	bool isEnabled() { return body_->IsEnabled(); }
	bool isBullet() { return body_->IsBullet(); }

	//setters
	void setType(b2BodyType t) { body_->SetType(t); }
	void setAwake(bool b) { body_->SetAwake(b); }
	void setEnabled(bool b) { body_->SetEnabled(b); }
	void setBullet(bool b) { body_->SetBullet(b); }
	void setTransform(b2Vec2 pos, float angle) { body_->SetTransform(pos, angle); }
	void setLinearVelocity(b2Vec2 vel) { body_->SetLinearVelocity(vel); }
	void applyLinearImpulse(b2Vec2 force, b2Vec2 point, bool wake) { body_->ApplyLinearImpulse(force, point, wake); }
	void applyForce(b2Vec2 force, b2Vec2 point, bool wake) { body_->ApplyForce(force, point, wake); }

private:
	float width_;
	float height_;
	b2Body* body_;
	b2World* world_;
	b2BodyDef bodyDef_;
	b2PolygonShape shape_;
	b2FixtureDef fixtureDef_;
};

