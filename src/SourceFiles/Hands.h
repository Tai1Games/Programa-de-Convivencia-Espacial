#pragma once
#include "Component.h"
#include "Texture.h"
#include "Collider.h"
class Hands : public Component
{
private:
	b2Vec2 pos_ = b2Vec2(0,0);
	double bodyOffset_ = 0;
	Texture* tex_ = nullptr;
	Collider* collider_ = nullptr;
	int textureId_;
	SDL_Rect clip_;

protected:
public:
	Hands();
	Hands(int textureId);
	Hands(int textureId, SDL_Rect clip);
	~Hands() {};
	virtual void init();
	virtual void draw() const;
	void setWeapon(int weaponColumn);
};

