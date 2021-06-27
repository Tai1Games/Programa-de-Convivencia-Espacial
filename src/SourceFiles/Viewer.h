#pragma once
#include "Component.h"
#include "checkML.h"
#include "AbstractViewers.h"
#include "Transform.h"

class Viewer : public Component, public AbstractViewers
{
protected:
	Transform* transform_;
	float angle = 0.0f;

public:
	Viewer();
	Viewer(int textureId, ComponentType::CmpId id = ComponentType::Viewer);

	virtual ~Viewer();

	virtual void init() override;
	virtual void update() override;
	virtual void draw() const override;

	Texture* setTexture(int text);
};
