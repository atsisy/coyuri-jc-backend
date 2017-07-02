#include "types.hpp"
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

KOMA_TYPE BANMEN::get_type(u8_t x, u8_t y) {
	return banmen[x][y];
}

void BANMEN::set_type(u8_t x, u8_t y, KOMA_TYPE type) {
      banmen[x][y] = type;
}


void BANMEN::copy_banmen(BANMEN *original) {
	for (u8_t x = 0; x < 9; x++) {
		for (u8_t y = 0; y < 9; y++) {
			this->banmen[x][y] = original->get_type(x, y);
		}
	}
}

KOMA_TYPE **BANMEN::get_banmen() {
	return this->banmen;
}

BANMEN *BANMEN::sasu(std::vector<Te> te_queue)
{
	BANMEN *result = new BANMEN;
	result->copy_banmen(this);
	Te te;
	KOMA_TYPE type;
	u8_t i, size;
	
	for (i = 0, size = te_queue.size(); i < size; ++i)
	{
		te = te_queue.at(i);
		if (te.from_x == 255)
		{
			/*
			*持ち駒から打たれる場合
			*/
			result->banmen[te.gone_x][te.gone_y] = te.type;
		}
		else {
			type = result->banmen[te.from_x][te.from_y];
			result->banmen[te.from_x][te.from_y] = EMPTY;
			result->banmen[te.gone_x][te.gone_y] = type;
		}
	}
	return result;

}

void BANMEN::sasu_to_src_ban(std::vector<Te> te_queue, BANMEN *for_result)
{
	for_result->copy_banmen(this);
	Te te;
	KOMA_TYPE type;
	u8_t i, size;

	for (i = 0, size = te_queue.size(); i < size; ++i)
	{
		te = te_queue.at(i);
		if (te.from_x == 255)
		{
			/*
			*持ち駒から打たれる場合
			*/
			for_result->banmen[te.gone_x][te.gone_y] = te.type;
		}
		else {
			type = for_result->banmen[te.from_x][te.from_y];
			for_result->banmen[te.from_x][te.from_y] = EMPTY;
			for_result->banmen[te.gone_x][te.gone_y] = type;
		}
	}
}