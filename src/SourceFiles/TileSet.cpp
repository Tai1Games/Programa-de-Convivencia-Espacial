#include "TileSet.h"

TileSet::TileSet() {
	tileW_ = tileH_ = 0;
	vMargin_ = hMargin_ = 0;
}

TileSet::TileSet(Texture* set, int w, int h, int mH, int mV) {
	TileSet();
	loadSet(set,w,h,mH,mV);
}

TileSet::~TileSet() {
	tileSet_ = nullptr;
}

void TileSet::loadSet(Texture* set,int w,int h, int mH,int mV) {
	tileSet_ = set;
	hMargin_ = mH; vMargin_ = mV;
	tileW_ = set->getWidth() / w - w * hMargin_;
	tileH_ = set->getHeight() / h - h * vMargin_;
	clips_.reserve(w*h);
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			SDL_Rect r{j+j*hMargin_,i+i*vMargin_,tileW_,tileH_};
			clips_[i + j] = r;
		}
	}
}
