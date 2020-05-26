#pragma once
#include "Component.h"
#include "Resources.h"
#include "Texture.h"
#include "Health.h"
#include "box2d.h"
#include "checkML.h"

class PlayerData;
class HealthViewer : public Component {
private:
	Texture* full = nullptr;	//Textura que se muestra si tenemos ese "toque"
	Texture* empty = nullptr;	//Textura que indica que ya no disponemos de ese "toque"

	Health* he = nullptr;		//Actualizar la lista de Componentes :D
	PlayerData* playerData_ = nullptr;
	b2Vec2 pos_;
	SDL_RendererFlip flip_;

	int activeTextureId_;
	int disableTextureId_;
	int lifeWidth_ = 0;
	int lifeHeight_ = 0;
	double lifeDrawOffset_ = 0;
	int playerSkin_;

	void setColorBySkin() const;

public:
	//Punteros a las 2 texturas de la vida y la posición de origen
	HealthViewer(int texActiveId , int texDisabledId,int skin);

	virtual ~HealthViewer() { full = nullptr; empty = nullptr; };

	void init() override;
	void update()override;
	void draw() const override;
	void handleInput()override;
	b2Vec2 getPos(){return pos_;};
	int getWidth() { return (he->getHealthMax() * (CONST(double, "LIFE_DRAW_OFFSET") + CONST(int,"LIFE_WIDTH"))); }
	void setPos(int player);
};