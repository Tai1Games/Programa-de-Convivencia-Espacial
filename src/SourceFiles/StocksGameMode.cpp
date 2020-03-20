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
	for(int i=0;i<players_.size();i++){
		Entity* e = players_[i];
		playersHealth_.push_back(e->getComponent<Health>(ComponentType::Health));
		HealthViewer* hV = (e->getComponent<HealthViewer>(ComponentType::HealthViewer));
		b2Vec2 p = hV->getPos();
		if (i % 2 == 0) {

			p.x += hV->getWidth() + STOCK_INITIAL_OFFSET;
		}
		else {
			p.x -= ((hV->getWidth()-LIFE_WIDTH) + STOCK_INITIAL_OFFSET + STOCK_WIDTH);
		}
		playersStocksPos_.push_back(p);
	}
}

void StocksGameMode::update(){

}

void StocksGameMode::render(){
	SDL_Rect drawPos;
	drawPos.w = STOCK_WIDTH;
	drawPos.h = STOCK_HEIGTH;		
	for(int i = 0;i<playerStocks_.size();++i){
		//if(i%2==0){
		//	drawPos.x +=  healtWidth_ + STOCK_INITIAL_OFFSET - STOCK_WIDTH - STOCK_OFFSET;
		//}
		//else{
		//	drawPos.x -=  STOCK_WIDTH - STOCK_INITIAL_OFFSET + STOCK_WIDTH + STOCK_OFFSET;
		//}
		drawPos.y = playersStocksPos_[i].y;
		for(int j = 0;j < playerStocks_[i];j++){
			if(i%2==0)
				drawPos.x = playersStocksPos_[i].x + j*(STOCK_WIDTH + STOCK_OFFSET);
			else
				drawPos.x = playersStocksPos_[i].x - j * (STOCK_WIDTH + STOCK_OFFSET);
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