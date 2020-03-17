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
	bool isText_ = false;
	b2Vec2 pos_;

public:
	Viewer();
	Viewer(int textureId);
	/*Constructor solo para textos*/
	Viewer(int textureId,float x,float y);
	Viewer(int textureId, SDL_Rect clip);
	virtual ~Viewer();

	virtual void init() override;
	virtual void draw() const override;
	void setDrawable(bool b) { drawable_ = b; }
};