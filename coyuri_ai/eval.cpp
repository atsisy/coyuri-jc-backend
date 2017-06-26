#include "types.hpp"
#include "values.hpp"
#include "prot.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <stdio.h>

extern std::function<std::vector<Point>(KOMA_TYPE **, Point)> wcm_function_table[29];
i64_t E_VALUE_ARRAY[29];

/*
*注
*ここで言う"敵"とはプレイヤーのこと
*"自分"というのはAIのこと
*/

i64_t EVAL(Node *node) {
	i64_t score = 10000;
	u8_t x, y, i, size;
	PiP _pip;
	KOMA_TYPE type;

	/*
	*盤面を評価
	*/

	MochiGomaGroup *mochi = node->pl_mochigoma;
	score += mochi->get(HU) * E_VALUE_ARRAY[HU >> 1];
	score += mochi->get(KYOUSHA) * E_VALUE_ARRAY[KYOUSHA >> 1];
	score += mochi->get(KEIMA) * E_VALUE_ARRAY[KEIMA >> 1];
	score += mochi->get(GIN) * E_VALUE_ARRAY[GIN >> 1];
	score += mochi->get(KIN) * E_VALUE_ARRAY[KIN >> 1];
	score += mochi->get(HISHA) * E_VALUE_ARRAY[HISHA >> 1];
	score += mochi->get(KAKU) * E_VALUE_ARRAY[KAKU >> 1];

	mochi = node->ai_mochigoma;
	score += mochi->get(EN_HU) * E_VALUE_ARRAY[EN_HU >> 1];
	score += mochi->get(EN_KYOUSHA) * E_VALUE_ARRAY[EN_KYOUSHA >> 1];
	score += mochi->get(EN_KEIMA) * E_VALUE_ARRAY[EN_KEIMA >> 1];
	score += mochi->get(EN_GIN) * E_VALUE_ARRAY[EN_GIN >> 1];
	score += mochi->get(EN_KIN) * E_VALUE_ARRAY[EN_KIN >> 1];
	score += mochi->get(EN_HISHA) * E_VALUE_ARRAY[EN_HISHA >> 1];
	score += mochi->get(EN_KAKU) * E_VALUE_ARRAY[EN_KAKU >> 1];

	for (i = 0, size = node->ai_on_board->size(); i < size; ++i) {
		_pip = node->ai_on_board->at(i);
		type = _pip_get_type(_pip);
		x = _pip_get_x(_pip);
		y = _pip_get_y(_pip);
		score += E_VALUE_ARRAY[type >> 1];
		if (_EQUALS(type, EN_HISHA) || _EQUALS(type, EN_RYU))
		{
			score += std::abs(node->ai_ou_point.x - x) << 3;
			score += std::abs(node->ai_ou_point.y - y) << 6;
		}
		else if (_EQUALS(type, EN_KAKU) || _EQUALS(type, EN_UMA))
		{
			score += std::abs(node->ai_ou_point.x - x) << 3;
			score += std::abs(node->ai_ou_point.y - y) << 6;
		}
		else if (_EQUALS(type, EN_KIN))
		{
			score -= (std::abs(node->ai_ou_point.x - x) << 4);
			score -= (std::abs(node->ai_ou_point.y - y) << 4);
		}
	}

	for (i = 0, size = node->pl_on_board->size(); i < size; ++i) {
		_pip = node->pl_on_board->at(i);
		type = _pip_get_type(_pip);
		x = _pip_get_x(_pip);
		y = _pip_get_y(_pip);
		score += E_VALUE_ARRAY[type >> 1];
		if (_EQUALS(type, HISHA) || _EQUALS(type, RYU))
		{
			score -= std::abs(node->pl_ou_point.x - x) << 3;
			score -= std::abs(node->pl_ou_point.y - y) << 6;
		}
		else if (_EQUALS(type, KAKU) || _EQUALS(type, UMA))
		{
			score -= std::abs(node->pl_ou_point.x - x) << 3;
			score -= std::abs(node->pl_ou_point.y - y) << 6;
		}
		else if (_EQUALS(type, KIN))
		{
			score += (std::abs(node->pl_ou_point.x - x) << 4);
			score += (std::abs(node->pl_ou_point.y - y) << 4);
		}
	}

	return score;
}

/*
*序盤での評価関数
*/
i64_t early_eval_function(Node *node) 
{
	u8_t i, x, y, size;
	KOMA_TYPE type;
	i64_t score = 10000;
	PiP _pip;

	for (i = 0, size = node->ai_on_board->size(); i < size; ++i) {
		_pip = node->ai_on_board->at(i);
		type = _pip_get_type(_pip);
		x = _pip_get_x(_pip);
		y = _pip_get_y(_pip);
		score += E_VALUE_ARRAY[type >> 1];
		
		if (_EQUALS(type, EN_HISHA) || _EQUALS(type, EN_RYU))
		{
			score += (std::abs(node->ai_ou_point.x - x));
			score += (std::abs(node->ai_ou_point.y - y) << 6);
		}
		else if (_EQUALS(type, EN_KAKU) || _EQUALS(type, EN_UMA))
		{
			score += (std::abs(node->ai_ou_point.x - x) << 4);
			score += (std::abs(node->ai_ou_point.y - y) << 4);
		}

	}

	return score;
}

/*
*渡された盤面からコンピュータがさせる手をすべてリストアップする関数
*/
void EXPAND(Node *node) {

	/*
     *AIが持ち駒を打つ場合
	 */
    u8_t i, size, n;
	KOMA_TYPE koma, may_get_koma;
	Point point_regi;
	std::vector<Point> points;
	bool ou_not_found = true;

	for (i = 0, size = node->ai_mochigoma->size(); i < size; ++i) {
		koma = node->ai_mochigoma->at(i);
		if (_IS_EMPTY(koma)) {
			continue;
		}
		node->ai_mochigoma->at(i) = EMPTY;

		if (_EQUALS(koma, EN_HU)) {
			points = ai_nihu_wcm(node->get_banmen()->get_banmen());
			for (n = 0; n < points.size();++n) {
				BANMEN *new_banmen = new BANMEN;
				new_banmen->copy_banmen(node->get_banmen());
				new_banmen->set_type(points.at(n).x, points.at(n).y, koma);
				node->get_children().push_back(new Node(new_banmen, node));
			}
		}
		else {
			points = tegoma_wcm(node->get_banmen()->get_banmen(), point(-1, -1));
			for (n = 0; n < points.size();++n) {
				BANMEN *new_banmen = new BANMEN;
				new_banmen->copy_banmen(node->get_banmen());
				new_banmen->set_type(points.at(n).x, points.at(n).y, koma);
				node->get_children().push_back(new Node(new_banmen, node));
			}
		}

		node->ai_mochigoma->at(i) = koma;
	}
	
	for (u8_t x = 0; x < 9; ++x) {
		for (u8_t y = 0; y < 9; ++y) {
			koma = node->get_banmen()->get_type(x, y);
			if (_IS_AI_KOMA(koma)) {
				points = wcm_function_table[_KOMA_TO_INDEX(koma)](node->get_banmen()->get_banmen(), point(x, y));
				size = points.size();
				for (u8_t n = 0; n < size; ++n) {
					point_regi = points.at(n);
					BANMEN *new_banmen = new BANMEN;
					new_banmen->copy_banmen(node->get_banmen());
					MochiGoma *ai_mochi = clone_mochigoma(node->ai_mochigoma);
					MochiGoma *pl_mochi = clone_mochigoma(node->pl_mochigoma);
					may_get_koma = node->get_banmen()->get_type(point_regi.x, point_regi.y);

					if (_IS_NOT_EMPTY(may_get_koma))
					{
						ai_mochi->push_back(_NEGAERI(may_get_koma));
					}

					if (point_regi.y >= 6) {
						/*
						*プレイヤーの陣地まで行ったので、成る処理をしたい
						*/
						new_banmen->set_type(point_regi.x, point_regi.y, naru_map.at(koma));
						new_banmen->set_type(x, y, EMPTY);
						node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
					}
					else {
						/*
						*成る処理は必要ない
						*/
						new_banmen->set_type(point_regi.x, point_regi.y, koma);
						new_banmen->set_type(x, y, EMPTY);
						node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
					}
				}
			}
		}
	}
}

/*
*渡された盤面からプレイヤーがさせる手をすべてリストアップする関数
*/
void PLAYER_EXPAND(Node *node) {
	/*
	*プレイヤーが持ち駒を打つ場合
	*/
	u8_t i, size, n;
	KOMA_TYPE koma, may_get_koma;
	std::vector<Point> points;
	Point point_regi;

	for (i = 0, size = node->pl_mochigoma->size(); i < size; ++i) {
		koma = node->pl_mochigoma->at(i);
		if (_IS_EMPTY(koma)) {
			continue;
		}
		node->pl_mochigoma->at(i) = EMPTY;

		if (_EQUALS(koma, HU)) {
			points = nihu_wcm(node->get_banmen()->get_banmen());
			for (n = 0; n < points.size();n++) {
				BANMEN *new_banmen = new BANMEN;
				new_banmen->copy_banmen(node->get_banmen());
				new_banmen->set_type(points.at(n).x, points.at(n).y, node->pl_mochigoma->at(i));
				node->get_children().push_back(new Node(new_banmen, node));
			}
		}
		else {
			points = tegoma_wcm(node->get_banmen()->get_banmen(), point(-1, -1));
			for (n = 0; n < points.size();++n) {
				BANMEN *new_banmen = new BANMEN;
				new_banmen->copy_banmen(node->get_banmen());
				new_banmen->set_type(points.at(n).x, points.at(n).y, node->pl_mochigoma->at(i));
				node->get_children().push_back(new Node(new_banmen, node));

			}
		}
		node->pl_mochigoma->at(i) = koma;
	}

	for (u8_t x = 0; x < 9; ++x) {
		for (u8_t y = 0; y < 9; ++y) {
			koma = node->get_banmen()->get_type(x, y);
			if (_IS_PLAYER_KOMA(koma)) {
				points = wcm_function_table[_KOMA_TO_INDEX(koma)](node->get_banmen()->get_banmen(), point(x, y));
				size = points.size();
				for (n = 0; n < size;++n) {
					point_regi = points.at(n);

					MochiGoma *pl_mochi = clone_mochigoma(node->pl_mochigoma);
					may_get_koma = node->get_banmen()->get_type(point_regi.x, point_regi.y);

					if (_IS_NOT_EMPTY(may_get_koma))
					{
						if (may_get_koma == EN_OU)
						{
							delete pl_mochi;
							continue;
						}
						else {
							pl_mochi->push_back(_NEGAERI(may_get_koma));
						}
					}

					BANMEN *new_banmen = new BANMEN;
					MochiGoma *ai_mochi = clone_mochigoma(node->ai_mochigoma);
					new_banmen->copy_banmen(node->get_banmen());
					
					if (point_regi.y <= 2 && _IS_AI_KOMA(koma)) {
						/*
						*なる必要がある
						*/
						new_banmen->set_type(point_regi.x, point_regi.y, naru_map.at(koma));
						new_banmen->set_type(x, y, EMPTY);
						node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
					}
					else {
						/*
						*なる必要は無い
						*/
						new_banmen->set_type(point_regi.x, points.at(n).y, koma);
						new_banmen->set_type(x, y, EMPTY);
						node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
					}
				}
			}
		}
	}
}
