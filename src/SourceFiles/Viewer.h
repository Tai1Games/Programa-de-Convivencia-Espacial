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
	Resources::TextureId textureId_;
	Texture* tex_;
	Collider* collider_;
	SDL_Rect clip_;
public:
	Viewer();
	Viewer(Resources::TextureId tex);
	Viewer(Resources::TextureId tex, SDL_Rect clip);
	virtual ~Viewer();

	virtual void init() override;
	virtual void draw() const override;
};