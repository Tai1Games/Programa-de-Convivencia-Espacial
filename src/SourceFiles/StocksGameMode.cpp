#include "StocksGameMode.h"
#include "Constants.h"

StocksGameMode::StocksGameMode(int stocks) : GameMode()
{
	maxStocks_ = stocks;
}

void StocksGameMode::init(PlayState* game){
	GameMode::init(game);
	for(int i = 0;i<players_.size();i++){
		playerStocks_.push_back(maxStocks_); //Initializes maxStocks vector with 3 on all positions.
	}
	for(int i=0;i<players_.size();i++){
		Entity* e = players_[i];
		playersHealth_.push_back(e->getComponent<Health>(ComponentType::Health)); //Initializes playersHealth vector catching a reference to Health on entity e.
		HealthViewer* hV = (e->getComponent<HealthViewer>(ComponentType::HealthViewer)); //Obtains a reference to the HealthViewer component of entity e. This is used to calculate where the stocks will be drawn
		b2Vec2 p = hV->getPos();
		if (i % 2 == 0) { //Players 1 & 3 will be drawn on the left side of the screen. Players 2 & 4 will be drawn on the right.
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
	SDL_Rect drawPos; //Position where the stocks will be drawn
	drawPos.w = STOCK_WIDTH;
	drawPos.h = STOCK_HEIGTH;
	for(int i = 0;i<playerStocks_.size();++i){ //i = player number, j = individual stock to be drawn
		drawPos.y = playersStocksPos_[i].y; //Stocks and Health are drawn on the same Y coordinate.
		for(int j = 0;j < playerStocks_[i];j++){ 
			if(i%2==0) //X coordinate depends on whether the stocks are drawn on the left or the right. 
				drawPos.x = playersStocksPos_[i].x + j*(STOCK_WIDTH + STOCK_OFFSET);
			else
				drawPos.x = playersStocksPos_[i].x - j * (STOCK_WIDTH + STOCK_OFFSET);
			SDL_Game::instance()->getTexturesMngr()->getTexture(Resources::Tinky)->render(drawPos);
		}
	}
}

bool StocksGameMode::onPlayerDead(int id) { //Returns false when player runs out of stocks
	if (id < playerStocks_.size()) {
		playerStocks_[id]--;
		if (playerStocks_[id] <= 0) { 
			roundResults_.push_back(players_[id]);
			if (roundResults_.size() == playerStocks_.size() - 1) roundFinished_ = true; //Round finishes when only 1 player remains
			return false;
		}
		else return true;
	}
	else return true;
}