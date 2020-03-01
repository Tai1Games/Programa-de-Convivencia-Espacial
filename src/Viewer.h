#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"
#include "Entity.h"
#include "checkML.h"


class Viewer :
	public Component
{
private:
protected:
	Texture* tex_;
	Transform* tr_;
	//SDL_Rect* clip;
public:
	Viewer();
	~Viewer();

	void init() override;
	void draw() const override;
};