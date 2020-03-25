#include "ProgressBar.h"

bool ProgressBar::addPoints(int sum) {
	actualProgress_ += sum;
	return actualProgress_ >= MAX_PROGRESS;
}