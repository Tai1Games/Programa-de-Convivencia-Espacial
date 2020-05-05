#pragma once
#include "Component.h"
#include "Texture.h"
#include "Entity.h"
#include "checkML.h"
#include "Collider.h"

class Viewer : public Component
{
protected:
	int textureId_;
	Texture* tex_;
	Collider* collider_;
	SDL_Rect clip_;
	bool drawable_ = true;
	b2Vec2 renderOffset_ = b2Vec2(0,0); //Use this if you want to draw the object a set distance from the collider.

public:
	Viewer();
	Viewer(int textureId);
	Viewer(int textureId, SDL_Rect clip);
	virtual ~Viewer();

	virtual void init() override;
	virtual void draw() const override;

	void setDrawable(bool b) { drawable_ = b; }
	void setClip(SDL_Rect clip) { clip_ = clip; }
	void setOffset(b2Vec2 newOffset) { renderOffset_ = newOffset; }
	Texture* getTexture() { return tex_; }
	int getTextureId() { return textureId_; }
};