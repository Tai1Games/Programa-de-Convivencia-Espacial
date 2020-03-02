#pragma once
#include "Component.h"
#include "Texture.h"
#include "Entity.h"
#include "checkML.h"
#include "Collider.h"


class Viewer :
	public Component
{
private:
protected:
	Texture* tex_;
	Collider* collider_;
	//SDL_Rect* clip;
public:
	Viewer();
	~Viewer();

	void init() override;
	void draw() const override;
};