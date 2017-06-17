#include "types.hpp"
#include "values.hpp"
#include "prot.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <stdio.h>

#define HU_EVAL		-10
#define KYOUSHA_EVAL -15
#define KEIMA_EVAL -15
#define GIN_EVAL -30
#define KIN_EVAL -50
#define HISHA_EVAL -100
#define KAKU_EVAL -95
#define OU_EVAL -1500
#define TOKIN_EVAL -55
#define NARIKYOU_EVAL -55
#define NARIKEI_EVAL -55
#define NARIGIN_EVAL -55
#define RYU_EVAL -150
#define UMA_EVAL -140

#define AI_HU_EVAL 10
#define AI_KYOUSHA_EVAL 15
#define AI_KEIMA_EVAL 15
#define AI_GIN_EVAL 30
#define AI_KIN_EVAL 50
#define AI_HISHA_EVAL 100
#define AI_KAKU_EVAL 95
#define AI_OU_EVAL 1500
#define AI_TOKIN_EVAL 55
#define AI_NARIKYOU_EVAL 55
#define AI_NARIKEI_EVAL 55
#define AI_NARIGIN_EVAL 55
#define AI_RYU_EVAL 150
#define AI_UMA_EVAL 140

KOMA_TYPE E_VALUE_ARRAY[] = {
	EMPTY,
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
	i64_t score = 0;

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
			score += E_VALUE_ARRAY[koma_to_index.at(node->get_banmen()->get_type(x, y))];
		}
	}
	
	MochiGoma *mochi = node->ai_mochigoma;
	for (i64_t i = 0; i < mochi->size(); ++i) {
		score += E_VALUE_ARRAY[koma_to_index.at(mochi->at(i))];
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

		if (_EQUALS(koma, HU)) { //もしも駒が歩（AIの持ち駒にあるのはEN_HUだが、&演算なので問題ない）
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
				points = function_table.at(koma)(node->get_banmen()->get_banmen(), point(x, y));
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
						ai_mochi->push_back(_PLAYER_TO_AI_NEGAERI(may_get_koma));
					}

					if (point_regi.y >= 7) {
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
				points = function_table.at(koma)(node->get_banmen()->get_banmen(), point(x, y));
				size = points.size();
				for (n = 0; n < size;++n) {
					point_regi = points.at(n);

					BANMEN *new_banmen = new BANMEN;
					new_banmen->copy_banmen(node->get_banmen());
					MochiGoma *ai_mochi = clone_mochigoma(node->ai_mochigoma);
					MochiGoma *pl_mochi = clone_mochigoma(node->pl_mochigoma);
					may_get_koma = node->get_banmen()->get_type(point_regi.x, point_regi.y);

					if (_IS_AI_KOMA(may_get_koma))
					{
						pl_mochi->push_back(_AI_TO_PLAYER_NEGAERI(may_get_koma));
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
