#pragma once
#include "Component.h"
#include "Texture.h"
#include "Entity.h"
#include "checkML.h"
#include "Collider.h"

class Viewer : public Component
{
private:
protected:
	int textureId_;
	Texture* tex_;
	Collider* collider_;
	SDL_Rect clip_;
	bool drawable_ = true;
	bool isUIElement_ = false;
	b2Vec2 pos_;
	float scale_ = 1;

public:
	Viewer();
	Viewer(int textureId);
	/*Constructor solo para UI elementos que no necesitan collider*/
	Viewer(int textureId,float x,float y, float scale);
	Viewer(int textureId, SDL_Rect clip);
	virtual ~Viewer();

	virtual void init() override;
	virtual void draw() const override;
	void setDrawable(bool b) { drawable_ = b; }
	/*Solo para UI elementos que no necesitan collider*/
	void setPosUIElement(b2Vec2 pos) { pos_ = pos; }
	/*Solo para UI elementos que no necesitan collider*/
	b2Vec2 getPosUIElement() { return pos_; }
};