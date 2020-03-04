#pragma once
#include "Component.h"
#include "box2d.h"

class Collider : public Component
{
public:
	Collider(b2World* world, b2BodyType type, float x, float y, float width, float height,
		float density, float friction, float restitution, int groupIndex, bool sensor);
	~Collider() {
		world_->DestroyBody(body_); world_ = nullptr;
	}

	//getters
	float getW(int i) { return width_[i]; }
	float getH(int i) { return height_[i]; }
	b2Vec2 getPos() { return body_->GetPosition(); }
	b2Vec2 getLinearVelocity() { return body_->GetLinearVelocity(); }
	b2BodyType getType() { return body_->GetType(); }
	b2Transform getTransform() { return body_->GetTransform(); }
	float getAngle() { return body_->GetAngle(); }
	float getMass() { return body_->GetMass(); }
	bool isAwake() { return body_->IsAwake(); }
	bool isSensor(int i) { return fixtureDef_[i].isSensor; }
	bool isEnabled() { return body_->IsEnabled(); }
	bool isBullet() { return body_->IsBullet(); }

	//setters
	void setType(b2BodyType t) { body_->SetType(t); }
	void setAwake(bool b) { body_->SetAwake(b); }
	void setEnabled(bool b) { body_->SetEnabled(b); }
	void setBullet(bool b) { body_->SetBullet(b); }
	void setTransform(b2Vec2 pos, float angle) { body_->SetTransform(pos, angle); }
	void setLinearVelocity(b2Vec2 vel) { body_->SetLinearVelocity(vel); }
	void applyLinearImpulse(b2Vec2 force, b2Vec2 point) { body_->ApplyLinearImpulse(force, point, true); }
	void applyForce(b2Vec2 force, b2Vec2 point) { body_->ApplyForce(force, point, true); }
	void createFixture(float width, float height, float density,
		float friction, float restitution, int groupIndex, bool sensor);

private:
	//general
	b2Body* body_;
	b2World* world_;
	b2BodyDef bodyDef_;

	//fixtures
	float width_[2];
	float height_[2];
	b2PolygonShape shape_[2];
	b2FixtureDef fixtureDef_[2];
};

