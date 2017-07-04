#include "types.hpp"
#include "values.hpp"
#include <iostream>


extern std::function<std::vector<Point>(KOMA_TYPE **, Point)> wcm_function_table[29];

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
			banmen[x][y] = original->get_type(x, y);
		}
	}
}

KOMA_TYPE **BANMEN::get_banmen() {
	return this->banmen;
}

Te BANMEN::search_diff(BANMEN *before) {

	Point diff_empty_point(0, 0);
	Te result_te;
	std::vector<Point> points;
	u8_t x, y;

	for (x = 0; x < 9; ++x) {
		for (y = 0; y < 9; ++y) {
			if (_IS_EMPTY(this->get_type(x, y)))
			{
				if (_IS_NOT_EMPTY(before->get_type(x, y)))
				{
					result_te.from_x = x;
					result_te.from_y = y;
					result_te.type = before->get_type(x, y);
				}
			}
		}
	}

	points = wcm_function_table[result_te.type](before->get_banmen(), Point(result_te.from_x, result_te.from_y));

	for (Point p : points) {

		if (this->get_type(p.x, p.y) == result_te.type)
		{
			if (this->get_type(p.x, p.y) != before->get_type(p.x, p.y))
			{
				result_te.from_x = x;
				result_te.from_y = y;
			}
		}

	}


}