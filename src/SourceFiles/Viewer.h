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
	int nFrames_ = 1;
	Texture* tex_;
	Collider* collider_;
	SDL_Rect clip_;
	bool drawable_ = true;
	b2Vec2 renderOffset_ = b2Vec2(0,0); //Use this if you want to draw the object a set distance from the collider.

public:
	Viewer();
	Viewer(int textureId, SDL_Rect clip = {0,0,0,0});
	Viewer(int textureId, SDL_Rect clip, ComponentType::CmpId id); //para herencia

	virtual ~Viewer();

	virtual void init() override;
	virtual void draw() const override;

	void setDrawable(bool b) { drawable_ = b; }
	void setClip(SDL_Rect clip) { clip_ = clip; }
	void setNFrames(int nFrames);
	void setOffset(b2Vec2 newOffset) { renderOffset_ = newOffset; }
	void setTexture(int text) { textureId_ = text; tex_ = SDL_Game::instance()->getTexturesMngr()->getTexture(textureId_); } //tiene que resetear la textura como tal
	void setScale(float scale) { scale_ = scale; }
	Texture* getTexture() { return tex_; }
	int getTextureId() { return textureId_; }
};
