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

	//Atributos para UI elements
	bool isUIElement_ = false;
	b2Vec2 pos_;
	b2Vec2 wH_;
	float scale_;
	/*En grados*/
	float angle_;
	SDL_RendererFlip flip_;

public:
	Viewer();
	Viewer(int textureId);
	Viewer(int textureId, SDL_Rect clip);
	/*Constructores solo para UI elementos que no necesitan collider*/
	Viewer(int textureId, b2Vec2 pos, float scale, float angle, const SDL_RendererFlip& flip = SDL_FLIP_NONE);
	Viewer(int textureId, b2Vec2 pos, float scale, float angle, SDL_Rect clip);
	virtual ~Viewer();

	virtual void init() override;
	virtual void draw() const override;
	void setDrawable(bool b) { drawable_ = b; }
	/*Solo para UI elementos que no necesitan collider*/
	void setPosUIElement(b2Vec2 pos) { pos_ = pos; }
	void setWHUIElement(b2Vec2 wH) { wH_ = wH; }
	void setClipUIElement(SDL_Rect clip) { clip_ = clip; }
	/*Solo para UI elementos que no necesitan collider*/
	b2Vec2 getPosUIElement() { return pos_; }
	b2Vec2 getWHUIElement() { return wH_; }
	SDL_Rect getClipUIElement() { return clip_; }
	int getTextureId() { return textureId_; }
};