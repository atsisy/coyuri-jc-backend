#include "types.hpp"
#include "values.hpp"
#include "prot.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <stdio.h>

i64_t E_VALUE_ARRAY[29];

/*
*注
*ここで言う"敵"とはプレイヤーのこと
*"自分"というのはAIのこと
*/

i64_t EVAL(Node *node) {
	i64_t score = 10000;
	u8_t x, y, size;
	BANMEN *ban;
	KOMA_TYPE type;

	/*
	*盤面を評価
	*/

	MochiGoma *mochi = node->pl_mochigoma;
	for (x = 0, size = mochi->size(); x < size; ++x) {
		score += E_VALUE_ARRAY[mochi->at(x) >> 1];
	}

	mochi = node->ai_mochigoma;
	for (x = 0, size = mochi->size(); x < size; ++x) {
		score += E_VALUE_ARRAY[mochi->at(x) >> 1];
	}
	
	ban = node->get_banmen();
	for (y = 0; y < 9; y++) {
		for (x = 0; x < 9; x++) {
			type = ban->get_type(x, y);
			if (!type)
			{
				continue;
			}
			score += E_VALUE_ARRAY[type >> 1];

			if (_EQUALS(type, EN_KIN))
			{
				score -= (std::abs(node->ai_ou_point.x - x) << 4);
				score -= (std::abs(node->ai_ou_point.y - y) << 4);
			}
			else if (_EQUALS(type, KIN))
			{
				score += (std::abs(node->pl_ou_point.x - x) << 4);
				score += (std::abs(node->pl_ou_point.y - y) << 4);
			}
			else if(_EQUALS(type, EN_HISHA) || _EQUALS(type, EN_RYU))
			{
				score += std::abs(node->ai_ou_point.y - y) << 6;
			}
			else if (_EQUALS(type, EN_KAKU) || _EQUALS(type, EN_UMA))
			{
				score += std::abs(node->ai_ou_point.x - x) << 3;
				score += std::abs(node->ai_ou_point.y - y) << 6;
			}
			else if (_EQUALS(type, HISHA) || _EQUALS(type, RYU))
			{
				score -= std::abs(node->pl_ou_point.y - y) << 6;
			}
			else if (_EQUALS(type, KAKU) || _EQUALS(type, UMA))
			{
				score -= std::abs(node->pl_ou_point.x - x) << 3;
				score -= std::abs(node->pl_ou_point.y - y) << 6;
			}
		}
	}

	return score;
}

/*
*序盤での評価関数
*/
i64_t early_eval_function(Node *node) 
{
	BANMEN *ban = node->get_banmen();
	u8_t x, y, size;
	KOMA_TYPE type;
	i64_t score = 10000;

	for (y = 0; y < 9; y++) {
		for (x = 0; x < 9; x++) {
			type = ban->get_type(x, y);
			if (!type)
			{
				continue;
			}
			score += E_VALUE_ARRAY[type >> 1];
			if (_EQUALS(type, EN_HISHA) || _EQUALS(type, EN_RYU))
			{
				score += (std::abs(node->ai_ou_point.y - y) << 6);
			}
			else if (_EQUALS(type, EN_KAKU) || _EQUALS(type, EN_UMA))
			{
				score += (std::abs(node->ai_ou_point.x - x) << 4);
				score += (std::abs(node->ai_ou_point.y - y) << 4);
			}
			else if (_EQUALS(type, EN_KIN))
			{
				score -= (std::abs(node->ai_ou_point.x - x) << 4);
				score -= (std::abs(node->ai_ou_point.y - y) << 4);
			}
			else if (_EQUALS(type, KIN))
			{
				score += (std::abs(node->pl_ou_point.x - x) << 4);
				score += (std::abs(node->pl_ou_point.y - y) << 4);
			}
		}
	}

	return score;
}

/*
*終盤での評価関数
*/
i64_t late_eval_function(Node *node)
{
	BANMEN *ban = node->get_banmen();
	u8_t x, y, size, pl_koma_num, pl_ou_x, pl_ou_y;
	KOMA_TYPE type;
	i64_t score = 10000;

	x = node->ai_ou_point.x;
	y = node->ai_ou_point.y;

	pl_ou_x = node->pl_ou_point.x;
	pl_ou_y = node->pl_ou_point.y;

	--x;
	if (_point_xy_error_check(x, y) && _IS_AI_KOMA(ban->get_type(x, y)))
	{
		score += 30;
	}
	x += 2;
	if (_point_xy_error_check(x, y) && _IS_AI_KOMA(ban->get_type(x, y)))
	{
		score += 30;
	}
	--y;
	if (_point_xy_error_check(x, y) && _IS_AI_KOMA(ban->get_type(x, y)))
	{
		score += 30;
	}
	--x;
	if (_point_xy_error_check(x, y) && _IS_AI_KOMA(ban->get_type(x, y)))
	{
		score += 30;
	}
	--x;
	if (_point_xy_error_check(x, y) && _IS_AI_KOMA(ban->get_type(x, y)))
	{
		score += 30;
	}
	y += 2;
	x += 2;
	if (_point_xy_error_check(x, y) && _IS_AI_KOMA(ban->get_type(x, y)))
	{
		score += 30;
	}
	--x;
	if (_point_xy_error_check(x, y) && _IS_AI_KOMA(ban->get_type(x, y)))
	{
		score += 30;
	}
	--x;
	if (_point_xy_error_check(x, y) && _IS_AI_KOMA(ban->get_type(x, y)))
	{
		score += 30;
	}

	for (y = 0; y < 9; y++) {
		for (x = 0; x < 9; x++) {
			type = ban->get_type(x, y);
			score += E_VALUE_ARRAY[type >> 1];
			if (_EQUALS(type, EN_HISHA) || _EQUALS(type, EN_RYU))
			{
				score -= (std::abs(pl_ou_x - x) << 2);
				score -= (std::abs(pl_ou_y - y) << 5);
			}
			else if (_EQUALS(type, EN_KAKU) || _EQUALS(type, EN_UMA))
			{
				score -= (std::abs(pl_ou_x - x) << 4);
				score -= (std::abs(pl_ou_y - y) << 4);
			}
		}
	}

	return score;
}
