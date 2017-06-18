#include "types.hpp"
#include "values.hpp"
#include "prot.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <stdio.h>

extern std::function<std::vector<Point>(KOMA_TYPE **, Point)> wcm_function_table[29];

constexpr i64_t AI_HU_EVAL = 10;
constexpr i64_t AI_KYOUSHA_EVAL = 15;
constexpr i64_t AI_KEIMA_EVAL = 15;
constexpr i64_t AI_GIN_EVAL = 30;
constexpr i64_t AI_KIN_EVAL = 60;
constexpr i64_t AI_HISHA_EVAL = 120;
constexpr i64_t AI_KAKU_EVAL = 110;
constexpr i64_t AI_OU_EVAL = 2000;
constexpr i64_t AI_TOKIN_EVAL = 45;
constexpr i64_t AI_NARIKYOU_EVAL = 50;
constexpr i64_t AI_NARIKEI_EVAL = 52;
constexpr i64_t AI_NARIGIN_EVAL = 58;
constexpr i64_t AI_RYU_EVAL = 160;
constexpr i64_t AI_UMA_EVAL = 150;

constexpr i64_t HU_EVAL = -AI_HU_EVAL;
constexpr i64_t KYOUSHA_EVAL = -AI_KYOUSHA_EVAL;
constexpr i64_t KEIMA_EVAL = -AI_KEIMA_EVAL;
constexpr i64_t GIN_EVAL = -AI_GIN_EVAL;
constexpr i64_t KIN_EVAL = -AI_KIN_EVAL;
constexpr i64_t HISHA_EVAL = -AI_HISHA_EVAL;
constexpr i64_t KAKU_EVAL = -AI_KAKU_EVAL;
constexpr i64_t OU_EVAL = -AI_OU_EVAL;
constexpr i64_t TOKIN_EVAL = -AI_TOKIN_EVAL;
constexpr i64_t NARIKYOU_EVAL = -AI_NARIKYOU_EVAL;
constexpr i64_t NARIKEI_EVAL = -AI_NARIKEI_EVAL;
constexpr i64_t NARIGIN_EVAL = -AI_NARIGIN_EVAL;
constexpr i64_t RYU_EVAL = -AI_RYU_EVAL;
constexpr i64_t UMA_EVAL = -AI_UMA_EVAL;


constexpr i64_t E_VALUE_ARRAY[] = {
	EMPTY,
	HU_EVAL,
	KYOUSHA_EVAL,
	KEIMA_EVAL,
	GIN_EVAL,
	KIN_EVAL,
	HISHA_EVAL,
	KAKU_EVAL,
	TOKIN_EVAL,
	NARIKYOU_EVAL,
	NARIKEI_EVAL,
	NARIGIN_EVAL,
	RYU_EVAL,
	UMA_EVAL,
	OU_EVAL,
	AI_HU_EVAL,
	AI_KYOUSHA_EVAL,
	AI_KEIMA_EVAL,
	AI_GIN_EVAL,
	AI_KIN_EVAL,
	AI_HISHA_EVAL,
	AI_KAKU_EVAL,
	AI_TOKIN_EVAL,
	AI_NARIKYOU_EVAL,
	AI_NARIKEI_EVAL,
	AI_NARIGIN_EVAL,
	AI_RYU_EVAL,
	AI_UMA_EVAL,
	AI_OU_EVAL,
};

/*
*注
*ここで言う"敵"とはプレイヤーのこと
*"自分"というのはAIのこと
*/

int EVAL(Node *node) {
	i64_t score = 5000;
	u8_t x, y;

	/*
	*盤面を評価
	*/

	/*
	*飛車が自分の陣地の外にいれば増加
	*/

	/*
	*角が自分の陣地の外にいれば増加
	*/

	/*
	*自分の陣地にプレーヤーの駒が入ってくる場合
	*/

	/*
	*自分の駒が盤面に何枚残っているか
	*/

	for (y = 0; y < 9; y++) {
		for (x = 0; x < 9; x++) {
			score += E_VALUE_ARRAY[node->get_banmen()->get_type(x, y) >> 1];
		}
	}

	MochiGoma *mochi = node->ai_mochigoma;
	for (x = 0; x < mochi->size(); ++x) {
		score += E_VALUE_ARRAY[mochi->at(x) >> 1];
	}

	mochi = node->pl_mochigoma;
	for (x = 0; x < mochi->size(); ++x) {
		score += E_VALUE_ARRAY[mochi->at(x) >> 1];
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

	for (i = 0; i < node->ai_mochigoma->size(); ++i) {
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
				node->get_children()->push_back(new Node(new_banmen, node));
			}
		}
		else {
			points = tegoma_wcm(node->get_banmen()->get_banmen(), point(-1, -1));
			for (n = 0; n < points.size();++n) {
				BANMEN *new_banmen = new BANMEN;
				new_banmen->copy_banmen(node->get_banmen());
				new_banmen->set_type(points.at(n).x, points.at(n).y, koma);
				node->get_children()->push_back(new Node(new_banmen, node));
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
						node->get_children()->push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
					}
					else {
						/*
						*成る処理は必要ない
						*/
						new_banmen->set_type(point_regi.x, point_regi.y, koma);
						new_banmen->set_type(x, y, EMPTY);
						node->get_children()->push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
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

	size = node->pl_mochigoma->size();
	for (i = 0; i < size; ++i) {
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
				node->get_children()->push_back(new Node(new_banmen, node));
			}
		}
		else {
			points = tegoma_wcm(node->get_banmen()->get_banmen(), point(-1, -1));
			for (n = 0; n < points.size();++n) {
				BANMEN *new_banmen = new BANMEN;
				new_banmen->copy_banmen(node->get_banmen());
				new_banmen->set_type(points.at(n).x, points.at(n).y, node->pl_mochigoma->at(i));
				node->get_children()->push_back(new Node(new_banmen, node));

			}
		}
		node->pl_mochigoma->at(i) = koma;
	}

	for (u8_t x = 0; x < 9; ++x) {
		for (u8_t y = 0; y < 9; ++y) {
			koma = node->get_banmen()->get_type(x, y);
			if (_IS_NOT_EMPTY(koma)) {
				points = wcm_function_table[_KOMA_TO_INDEX(koma)](node->get_banmen()->get_banmen(), point(x, y));
				size = points.size();
				for (n = 0; n < size;++n) {
					point_regi = points.at(n);

					BANMEN *new_banmen = new BANMEN;
					new_banmen->copy_banmen(node->get_banmen());
					MochiGoma *ai_mochi = clone_mochigoma(node->ai_mochigoma);
					MochiGoma *pl_mochi = clone_mochigoma(node->pl_mochigoma);
					may_get_koma = node->get_banmen()->get_type(point_regi.x, point_regi.y);

					if (_IS_NOT_EMPTY(may_get_koma))
					{
						pl_mochi->push_back(_NEGAERI(may_get_koma));
					}
					
					if (point_regi.y <= 2 && _IS_AI_KOMA(koma)) {
						/*
						*なる必要がある
						*/
						new_banmen->set_type(point_regi.x, point_regi.y, naru_map.at(koma));
						new_banmen->set_type(x, y, EMPTY);
						node->get_children()->push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
					}
					else {
						/*
						*なる必要は無い
						*/
						new_banmen->set_type(point_regi.x, points.at(n).y, koma);
						new_banmen->set_type(x, y, EMPTY);
						node->get_children()->push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
					}
				}
			}

		}
	}
}
