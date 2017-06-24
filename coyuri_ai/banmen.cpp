#include "types.hpp"
#include "values.hpp"
#include <iostream>

BANMEN::BANMEN() {
	banmen = new KOMA_TYPE *[9];

	for (u8_t i = 0; i < 9; ++i) {
		banmen[i] = new KOMA_TYPE[9];
	}
}


BANMEN::~BANMEN() {
	for (u8_t i = 0; i < 9; ++i) {
		delete[] banmen[i];
	}

	delete[] banmen;
}

KOMA_TYPE BANMEN::get_type(int x, int y) {
	return banmen[x][y];
}

void BANMEN::set_type(int x, int y, KOMA_TYPE type) {
      banmen[x][y] = type;
}


void BANMEN::copy_banmen(BANMEN *original) {
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			banmen[x][y] = original->get_type(x, y);
		}
	}
}

KOMA_TYPE **BANMEN::get_banmen() {
	return this->banmen;
}
