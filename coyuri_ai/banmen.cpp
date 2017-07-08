#include "types.hpp"
#include "values.hpp"
#include <iostream>


extern std::function<std::vector<Point>(BANMEN *, Point)> wcm_function_table[29];

BANMEN::BANMEN() {
}


BANMEN::~BANMEN() {
}

void BANMEN::set_type(u8_t x, u8_t y, KOMA_TYPE type) {
      banmen[_BANMEN_VECTOR_TO_SCALAR(x, y)] = type;
}


void BANMEN::copy_banmen(BANMEN *original) {
	for (u8_t x = 0; x < 9; x++) {
		for (u8_t y = 0; y < 9; y++) {
			banmen[_BANMEN_VECTOR_TO_SCALAR(x, y)] = original->get_type(x, y);
		}
	}
}

Te BANMEN::search_diff(BANMEN *new_banmnen) {

	Point diff_empty_point(0, 0);
	Te result_te;
	std::vector<Point> points;
	u8_t x, y;

	for (x = 0; x < 9; ++x) {
		for (y = 0; y < 9; ++y) {
			if (_IS_EMPTY(new_banmnen->get_type(x, y)))
			{
				if (_IS_NOT_EMPTY(this->get_type(x, y)))
				{
					result_te.from_x = x;
					result_te.from_y = y;
					result_te.type = this->get_type(x, y);
				}
			}
		}
	}

	points = wcm_function_table[_KOMA_TO_INDEX(result_te.type)](this, Point(result_te.from_x, result_te.from_y));

	for (Point p : points) {
		if (new_banmnen->get_type(p.x, p.y) == result_te.type || new_banmnen->get_type(p.x, p.y) == naru_map.at(result_te.type))
		{
			if (new_banmnen->get_type(p.x, p.y) != this->get_type(p.x, p.y))
			{
				result_te.gone_x = p.x;
				result_te.gone_y = p.y;
			}
		}
	}

	return result_te;
}

Point find_ai_ou(BANMEN *ban)
{
	u8_t x, y;
	for (x = 0; x < 9; ++x) {
		for (y = 0; y < 9; ++y) {
			if (_EQUALS(ban->get_type(x, y), EN_OU))
			{
				return Point(x, y);
			}
		}
	}

	return Point(0, 0);
}

Point find_pl_ou(BANMEN *ban)
{
	u8_t x, y;
	for (x = 0; x < 9; ++x) {
		for (y = 0; y < 9; ++y) {
			if (_EQUALS(ban->get_type(x, y), OU))
			{
				return Point(x, y);
			}
		}
	}

	return Point(0, 0);
}