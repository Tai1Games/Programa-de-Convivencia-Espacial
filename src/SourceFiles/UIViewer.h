#pragma once
#include "Component.h"
class UIViewer : public Component
{
protected:
	int textureId_;
	Texture* tex_;
	SDL_Rect clip_;
	bool drawable_ = true;

	b2Vec2 pos_;
	b2Vec2 wH_;
	float scale_;
	/*En grados*/
	float angle_;
	SDL_RendererFlip flip_;
public:
	UIViewer(int textureId, b2Vec2 pos, float scale, float angle, const SDL_RendererFlip& flip = SDL_FLIP_NONE);
	UIViewer(int textureId, b2Vec2 pos, float scale, float angle, SDL_Rect clip);
	virtual ~UIViewer();

	virtual void init() override;
	virtual void draw() const override;

	void setDrawable(bool b) { drawable_ = b; }
	void setClip(SDL_Rect clip) { clip_ = clip; }
	/*Solo para UI elementos que no necesitan collider*/
	void setPosUIElement(b2Vec2 pos) { pos_ = pos; }
	void setWHUIElement(b2Vec2 wH) { wH_ = wH; }
	/*Solo para UI elementos que no necesitan collider*/
	b2Vec2 getPosUIElement() { return pos_; }
	b2Vec2 getWHUIElement() { return wH_; }
	SDL_Rect getClipUIElement() { return clip_; }
	Texture* getTexture() { return tex_; }
	int getTextureId() { return textureId_; }


};

