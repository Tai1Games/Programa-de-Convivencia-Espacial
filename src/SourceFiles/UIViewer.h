#pragma once
#include "Component.h"
#include "AbstractViewers.h"

class UIViewer : public Component, public AbstractViewers
{
protected:
	b2Vec2 pos_;
	float scale_;
	/*En grados*/
	float angle_;
	SDL_RendererFlip flip_;
public:
	UIViewer(int textureId, b2Vec2 pos, float scale, float angle = 0, const SDL_RendererFlip& flip = SDL_FLIP_NONE, ComponentType::CmpId id = ComponentType::UIViewer);

	virtual ~UIViewer();

	virtual void init() override;
	virtual void draw() const override;

	void setPosUIElement(b2Vec2 pos) { pos_ = pos; }
	void setWHUIElement(b2Vec2 wH) { wH_ = wH; }
	void setScale(float scale) { scale_ = scale; }

	int getW();
	int getH();

	b2Vec2 getPosUIElement() { return pos_; }
	b2Vec2 getWHUIElement() { return b2Vec2(wH_.x * scale_, wH_.y * scale_); }
};
