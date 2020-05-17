#pragma once
#include "Component.h"
#include "checkML.h"
#include "AbstractViewers.h"
#include "Collider.h"

class Viewer : public Component, public AbstractViewers
{
protected:
	Collider* collider_;
public:
	Viewer();
	Viewer(int textureId, ComponentType::CmpId id = ComponentType::Viewer);

	virtual ~Viewer();

	virtual void init() override;
	virtual void draw() const override;

	void setTexture(int text) { textureId_ = text; tex_ = SDL_Game::instance()->getTexturesMngr()->getTexture(textureId_); } //tiene que resetear la textura como tal
};
