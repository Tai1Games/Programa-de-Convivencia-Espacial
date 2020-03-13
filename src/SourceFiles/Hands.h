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
	int playerID_ = -1;
protected:
public:
	Hands(int playerID, int textureId);
	Hands(int playerID, int textureId, SDL_Rect clip);
	~Hands() {};
	virtual void init();
	virtual void draw() const;
	void setWeapon(int weaponColumn);
	int getPlayerId() { return playerID_; }
};
