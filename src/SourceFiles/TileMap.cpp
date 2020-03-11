#include "TileMap.h"
#include "SDL_Game.h"
#include "Resources.h"

int lvl1[9][16] = {
	{1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0},
	{0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
TileMap::TileMap() {
	SDLTexturesManager* tm = SDL_Game::instance()->getTexturesMngr();
	tinkyT_ = tm->getTexture(Resources::Tinky);
	debugT_ = tm->getTexture(Resources::Debug);
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9; column++) {
			map_[row][column] = lvl1[row][column];
		}
	}
}

void TileMap::drawMap() {
	int t = 0;
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 16; column++) {
			t = map_[row][column];

			switch (t)
			{
			case (1):
				tinkyT_->render({ column*SIZE,row* SIZE,SIZE,SIZE });
				break;
			case (0):
				debugT_->render({ column * SIZE,row * SIZE,SIZE,SIZE });
				break;
			default:
				
				break;
			}
		}
	}
}
