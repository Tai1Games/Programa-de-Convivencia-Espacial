#include "HealthViewer.h"
#include "Entity.h"
#include "PlayerData.h"

HealthViewer::HealthViewer(int texActiveId, int texDisabledId) : Component(ComponentType::HealthViewer)
{
	activeTextureId_ = texActiveId;
	disableTextureId_ = texDisabledId;

}

void HealthViewer::init()
{
	//Diria que no hace falta poner nada mas...
	playerData_ = GETCMP1_(PlayerData);
	he = GETCMP1_(Health);
	full = SDL_Game::instance()->getTexturesMngr()->getTexture(activeTextureId_);
	empty = SDL_Game::instance()->getTexturesMngr()->getTexture(disableTextureId_);
	setPos(playerData_->getPlayerNumber());
}
void HealthViewer::update()
{
	//Todo lo hace el draw, este no sirve ninguna función 
}
void HealthViewer::draw() const
{
	int player = playerData_->getPlayerNumber();
	SDL_Rect dest = {pos_.x,pos_.y,LIFE_WIDTH,LIFE_HEIGTH};
	for (int i = 0; i < he->getHealthMax(); i++) {
		if (player % 2 == 0){
			dest.x = pos_.x + i*((LIFE_WIDTH + LIFE_DRAW_OFFSET));
		}
		else{
			dest.x = pos_.x -(i*((LIFE_WIDTH + LIFE_DRAW_OFFSET)));
		}

		if ((i+1) <= he->getHealth()) {		//Si tiene esas X vidas las muertra como llenas
			full->render(dest, 0, SDL_Rect{ 0, 0, 613,667 });
		}
		else {		//Si no las tiene, se dibujarán como vacias
			empty->render(dest, 0, SDL_Rect{ 0, 0, 613,667 });
		}
	}

}

void HealthViewer::handleInput() {

}

void HealthViewer::setPos(int player){
	pos_.x = (player % 2 == 0) ? (LIFE_MARGIN_H) : (WINDOW_WIDTH - LIFE_MARGIN_H- LIFE_WIDTH);
	pos_.y = (player < 2) ? (CONST(double,"LIFE_MARGIN_V")) : (WINDOW_HEIGHT - CONST(double,"LIFE_MARGIN_V") - LIFE_HEIGTH);
}