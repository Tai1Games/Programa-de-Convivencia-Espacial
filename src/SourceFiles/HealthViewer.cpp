#include "HealthViewer.h"
#include "Entity.h"
#include "PlayerData.h"

HealthViewer::HealthViewer(int texActiveId, int texDisabledId,int skin) : Component(ComponentType::HealthViewer)
{
	activeTextureId_ = texActiveId;
	disableTextureId_ = texDisabledId;
	playerSkin_ = skin;
}

void HealthViewer::init()
{
	//Diria que no hace falta poner nada mas...
	playerData_ = GETCMP1_(PlayerData);
	he = GETCMP1_(Health);
	full = SDL_Game::instance()->getTexturesMngr()->getTexture(activeTextureId_);
	empty = SDL_Game::instance()->getTexturesMngr()->getTexture(disableTextureId_);
	int playerNumber = playerData_->getPlayerNumber();
	setPos(playerNumber);
	flip_ = (playerNumber % 2 == 0) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

	lifeWidth_ = CONST(int, "LIFE_WIDTH");
	lifeHeight_ = CONST(int, "LIFE_HEIGTH");
	lifeDrawOffset_ = CONST(double, "LIFE_DRAW_OFFSET");
	
	setColorBySkin();

}
void HealthViewer::update()
{
	//Todo lo hace el draw, este no sirve ninguna función 
}
void HealthViewer::draw() const
{
	int player = playerData_->getPlayerNumber();

	SDL_Rect dest = {pos_.x,pos_.y, lifeWidth_, lifeHeight_};
	for (int i = 0; i < he->getHealthMax(); i++) {
		if (player % 2 == 0){
			dest.x = pos_.x + i*(lifeWidth_ + lifeDrawOffset_);
		}
		else{
			dest.x = pos_.x -(i*(lifeWidth_ + lifeDrawOffset_));
		}

		if ((i+1) <= he->getHealth()) {		//Si tiene esas X vidas las muertra como llenas
			full->render(dest, 0, SDL_Rect{ 0, 0, 613,667 },flip_);
		}
		else {		//Si no las tiene, se dibujarán como vacias
			empty->render(dest, 0, SDL_Rect{ 0, 0, 613,667 },flip_);
		}
	}

}

void HealthViewer::handleInput() {

}

void HealthViewer::setPos(int player){
	pos_.x = (player % 2 == 0) ? (CONST(int,"LIFE_MARGIN_H")) : (CONST(int,"WINDOW_WIDTH") - CONST(int,"LIFE_MARGIN_H")- CONST(int,"LIFE_WIDTH"));
	pos_.y = (player < 2) ? (CONST(double,"LIFE_MARGIN_V")) : (CONST(int,"WINDOW_HEIGHT") - CONST(double,"LIFE_MARGIN_V") - CONST(int,"LIFE_HEIGTH"));
}

void HealthViewer::setColorBySkin()
{
	switch (playerSkin_)
	{
	case 0:
	case 1:
		full->setColor(SDL_Color{ 199, 220, 208 });
		break;
	case 2:
	case 3:
		full->setColor(SDL_Color{ 232, 59, 59 });
		break;
	case 4:
	case 5:
		full->setColor(SDL_Color{ 77, 155, 230 });
		break;
	case 6:
	case 7:
		full->setColor(SDL_Color{ 145, 219, 105 });
		break;
	case 8:
	case 9:
		full->setColor(SDL_Color{ 249, 194, 43 });
		break;
	default:
		break;
	}
}
