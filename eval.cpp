#include "types.hpp"
#include "values.hpp"
#include "prot.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <stdio.h>

const int WITHIN_OU = 5;
const int WITHIN_HISHA = 3;
const int WITHIN_KAKU = 2;
const int WITHIN_PLAYER = -15;
const int PLAYER_HISHA = 30;
const int PLAYER_KAKU = 27;
const int AI_KOMA_FORWARD = 20;

static const int HU_EVAL = 10;
static const int KYOUSHA_EVAL = 15;
static const int KEIMA_EVAL = 15;
static const int GIN_EVAL = 30;
static const int KIN_EVAL = 50;
static const int HISHA_EVAL = 100;
static const int KAKU_EVAL = 95;
static const int OU_EVAL = 1200;
static const int TOKIN_EVAL = 55;
static const int NARIKYOU_EVAL = 55;
static const int NARIKEI_EVAL = 55;
static const int NARIGIN_EVAL = 55;
static const int RYU_EVAL = 150;
static const int UMA_EVAL = 140;

static const int AI_HU_EVAL = 10;
static const int AI_KYOUSHA_EVAL = 15;
static const int AI_KEIMA_EVAL = 15;
static const int AI_GIN_EVAL = 30;
static const int AI_KIN_EVAL = 50;
static const int AI_HISHA_EVAL = 100;
static const int AI_KAKU_EVAL = 95;
static const int AI_OU_EVAL = 1200;
static const int AI_TOKIN_EVAL = 55;
static const int AI_NARIKYOU_EVAL = 55;
static const int AI_NARIKEI_EVAL = 55;
static const int AI_NARIGIN_EVAL = 55;
static const int AI_RYU_EVAL = 150;
static const int AI_UMA_EVAL = 140;

/*
*注
*ここで言う"敵"とはプレイヤーのこと
*"自分"というのはAIのこと
*/

int EVAL(Node *node) {
	i32_t score = 0;
	u8_t counters[30] = { 0 };

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

	for (u8_t y = 0; y < 9; y++) {
		for (u8_t x = 0; x < 9; x++) {
			++counters[koma_to_index.at(node->get_banmen()->get_type(x, y))];
		}
	}

	score -= counters[2] * HU_EVAL;
	score -= (counters[3] << 4);
	score -= counters[4] * KEIMA_EVAL;
	score -= counters[5] * GIN_EVAL;
	score -= counters[6] * KIN_EVAL;
	score -= counters[7] * HISHA_EVAL;
	score -= counters[8] * KAKU_EVAL;
	score -= counters[9] * TOKIN_EVAL;
	score -= counters[10] * NARIKYOU_EVAL;
	score -= counters[11] * NARIKEI_EVAL;
	score -= counters[12] * NARIGIN_EVAL;
	score -= counters[13] * RYU_EVAL;
	score -= counters[14] * UMA_EVAL;
	score -= counters[15] * OU_EVAL;
	score += counters[16] * AI_HU_EVAL;
	score += (counters[17] << 4);
	score += counters[18] * AI_KEIMA_EVAL;
	score += counters[19] * AI_GIN_EVAL;
	score += counters[20] * AI_KIN_EVAL;
	score += counters[21] * AI_HISHA_EVAL;
	score += counters[22] * AI_KAKU_EVAL;
	score += counters[23] * AI_TOKIN_EVAL;
	score += counters[24] * AI_NARIKYOU_EVAL;
	score += counters[25] * AI_NARIKEI_EVAL;
	score += counters[26] * AI_NARIGIN_EVAL;
	score += counters[27] * AI_RYU_EVAL;
	score += counters[28] * AI_UMA_EVAL;
	score += (counters[29] << 11);

	return score;
}

/*
*渡された盤面からコンピュータがさせる手をすべてリストアップする関数
*/
void EXPAND(Node *node) {

	/*
       *AIが持ち駒を打つ場合
       */
    u8_t i, size;
	KOMA_TYPE koma, may_get_koma;
	for (i = 0; i < node->ai_mochigoma->size(); ++i) {
		koma = node->ai_mochigoma->at(i);
		if (_IS_EMPTY(koma)) {
			continue;
		}
		node->ai_mochigoma->at(i) = EMPTY;

		if (_EQUALS(koma, HU)) { //もしも駒が歩（AIの持ち駒にあるのはEN_HUだが、&演算なので問題ない）
			for (Point p : ai_nihu_wcm(node->get_banmen()->get_banmen())) {
				BANMEN *new_banmen = new BANMEN;
				new_banmen->copy_banmen(node->get_banmen());
				new_banmen->set_type(p.get_x(), p.get_y(), koma);
				node->get_children()->push_back(new Node(new_banmen, node));
			}
		}
		else {
			for (Point p : tegoma_wcm(node->get_banmen()->get_banmen(), Point(-1, -1))) {
				BANMEN *new_banmen = new BANMEN;
				new_banmen->copy_banmen(node->get_banmen());
				new_banmen->set_type(p.get_x(), p.get_y(), koma);
				node->get_children()->push_back(new Node(new_banmen, node));
			}
		}

		
		node->ai_mochigoma->at(i) = koma;
	}
	
	std::vector<Point> points;
	for (u8_t x = 0; x < 9; ++x) {
		for (u8_t y = 0; y < 9; ++y) {
			koma = node->get_banmen()->get_type(x, y);
			if (_IS_AI_KOMA(koma)) {
				points = function_table.at(koma)(node->get_banmen()->get_banmen(), Point(x, y));
				size = points.size();
				for (u8_t n = 0; n < size; ++n) {
					BANMEN *new_banmen = new BANMEN;
					new_banmen->copy_banmen(node->get_banmen());
					MochiGoma *ai_mochi = clone_mochigoma(node->ai_mochigoma);
					MochiGoma *pl_mochi = clone_mochigoma(node->pl_mochigoma);
					may_get_koma = node->get_banmen()->get_type(points.at(n).get_x(), points.at(n).get_y());

					if (_IS_NOT_EMPTY(may_get_koma))
					{
						ai_mochi->push_back(_PLAYER_TO_AI_NEGAERI(may_get_koma));
					}

					if (points.at(n).get_y() >= 7 && _IS_AI_KOMA(koma)) {
						/*
						*プレイヤーの陣地まで行ったので、成る処理をしたい
						*/
						
						new_banmen->set_type(points.at(n).get_x(), points.at(n).get_y(), naru_map.at(koma));
						new_banmen->set_type(x, y, EMPTY);
						node->get_children()->push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
					}
					else {
						/*
						*成る処理は必要ない
						*/
						new_banmen->set_type(points.at(n).get_x(), points.at(n).get_y(), koma);
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

	for (i = 0; i < node->pl_mochigoma->size(); ++i) {
		koma = node->pl_mochigoma->at(i);
		if (_IS_EMPTY(koma)) {
			continue;
		}
		node->pl_mochigoma->at(i) = EMPTY;

		if (_EQUALS(koma, HU)) {
			for (Point p : nihu_wcm(node->get_banmen()->get_banmen())) {
				BANMEN *new_banmen = new BANMEN;
				new_banmen->copy_banmen(node->get_banmen());
				new_banmen->set_type(p.get_x(), p.get_y(), node->pl_mochigoma->at(i));
				node->get_children()->push_back(new Node(new_banmen, node));
			}
		}
		else {
			for (Point p : tegoma_wcm(node->get_banmen()->get_banmen(), Point(-1, -1))) {
				BANMEN *new_banmen = new BANMEN;
				new_banmen->copy_banmen(node->get_banmen());
				new_banmen->set_type(p.get_x(), p.get_y(), node->pl_mochigoma->at(i));
				node->get_children()->push_back(new Node(new_banmen, node));

			}
		}
		node->pl_mochigoma->at(i) = koma;
	}

	for (u8_t x = 0; x < 9; ++x) {
		for (u8_t y = 0; y < 9; ++y) {
			koma = node->get_banmen()->get_type(x, y);
			if (_IS_NOT_EMPTY(koma)) {
				points = function_table.at(koma)(node->get_banmen()->get_banmen(), Point(x, y));
				size = points.size();
				for (n = 0; n < size;++n) {
					BANMEN *new_banmen = new BANMEN;
					new_banmen->copy_banmen(node->get_banmen());
					MochiGoma *ai_mochi = clone_mochigoma(node->ai_mochigoma);
					MochiGoma *pl_mochi = clone_mochigoma(node->pl_mochigoma);
					may_get_koma = node->get_banmen()->get_type(points.at(n).get_x(), points.at(n).get_y());

					if (_IS_AI_KOMA(may_get_koma))
					{
						pl_mochi->push_back(_AI_TO_PLAYER_NEGAERI(may_get_koma));
					}
					
					if (points.at(n).get_y() <= 2 && _IS_AI_KOMA(koma)) {
						/*
						*なる必要がある
						*/
						new_banmen->set_type(points.at(n).get_x(), points.at(n).get_y(), naru_map.at(koma));
						new_banmen->set_type(x, y, EMPTY);
						node->get_children()->push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
					}
					else {
						/*
						*なる必要は無い
						*/
						new_banmen->set_type(points.at(n).get_x(), points.at(n).get_y(), koma);
						new_banmen->set_type(x, y, EMPTY);
						node->get_children()->push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
					}
				}
			}

		}
	}
}
