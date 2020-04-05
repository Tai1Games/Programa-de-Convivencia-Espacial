#include "SRandBasedGenerator.h"

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <assert.h>

using namespace std;

SRandBasedGenerator::SRandBasedGenerator() :
		seed_(std::time(0)) {
}

SRandBasedGenerator::SRandBasedGenerator(unsigned seed) :
		seed_(seed) {
	init();
}

SRandBasedGenerator::~SRandBasedGenerator() {
}

void SRandBasedGenerator::init() {
	srand(seed_);
}

int SRandBasedGenerator::nextInt() {
	return rand();
}

int SRandBasedGenerator::nextInt(int low, int high) {
	assert(low < high);
	return low + (nextInt() % (high - low));
}
