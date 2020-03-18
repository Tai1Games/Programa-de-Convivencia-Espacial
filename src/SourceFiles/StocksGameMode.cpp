#include "StocksGameMode.h"
#include "Constants.h"

StocksGameMode::StocksGameMode(int stocks) : GameMode()
{
	maxStocks_ = stocks;
}

void StocksGameMode::init(PlayState* game){
	GameMode::init(game);
	for(int i = 0;i<players_.size();i++){
		playerStocks_.push_back(maxStocks_);
	}
	for(Entity* e:players_){
		playersHealth_.push_back(e->getComponent<Health>(ComponentType::Health));
		playersHealthViewerPos_.push_back(e->getComponent<HealthViewer>(ComponentType::HealthViewer)->getPos());
		e->getComponent<HealthViewer>(ComponentType::HealthViewer)->getWidth();	
	}
}

void StocksGameMode::update(){

}

void StocksGameMode::render(){
	SDL_Rect drawPos;
	drawPos.w = STOCK_WIDTH;
	drawPos.h = STOCK_HEIGTH;		
	for(int i = 0;i<playerStocks_.size();++i){
		drawPos.x = playersHealthViewerPos_[i].x;
		drawPos.y = playersHealthViewerPos_[i].y;
		if(i%2==0){
			drawPos.x +=  healtWidth_ + STOCK_INITIAL_OFFSET;
		}
		else{
			drawPos.x -=  healtWidth_ - STOCK_WIDTH - STOCK_INITIAL_OFFSET;
		}
		for(int j = 0;j < playerStocks_[i];j++){
			if(i%2==0)
				drawPos.x += STOCK_WIDTH + STOCK_OFFSET;
			else
				drawPos.x -= STOCK_WIDTH - STOCK_OFFSET;
			SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Tinky)->render(drawPos);
		}
	}
}

bool StocksGameMode::onPlayerDead(Health* h){
	int i = 0;
	while (i < playersHealth_.size() && playersHealth_[i] != h) { i++; }
	playerStocks_[i]--;
	if (playerStocks_[i] <= 0) return false;
	else return true; 
}