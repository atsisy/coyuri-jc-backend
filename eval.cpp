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

int within_ou(BANMEN *banmen);
int within_hisha(BANMEN *banmen);
int within_kaku(BANMEN *banmen);
int within_player(BANMEN *banmen);
int num_on_ban(BANMEN	 *banmen);
int player_hisha(BANMEN *banmen);
int player_kaku(BANMEN *banmen);

/*
*注
*ここで言う"敵"とはプレイヤーのこと
*"自分"というのはAIのこと
*/

int EVAL(Node *node) {
	int score = 0;
	u8_t counters[30] = { 0 };
	u8_t scores[10] = { 0 };

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

	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {

			/*

			if (y < 3) {
				if (node->get_banmen()->get_type(x, y) >= HU && node->get_banmen()->get_type(x, y) < OU) {
					scores[0]++;
				}
			}
			if (!(node->get_banmen()->get_type(x, y) - EN_OU)) {
				if (y <= 7) {
					if (node->get_banmen()->get_type(x, y + 1) >= EN_HU && node->get_banmen()->get_type(x, y + 1) < EN_OU) {
						scores[1]++;
					}
					if (x <= 1 && node->get_banmen()->get_type(x - 1, y + 1) >= EN_HU && node->get_banmen()->get_type(x - 1, y + 1) < EN_OU) {
						scores[1]++;
					}
					if (x < 8 && node->get_banmen()->get_type(x + 1, y + 1) >= EN_HU && node->get_banmen()->get_type(x + 1, y + 1) < EN_OU) {
						scores[1]++;
					}
				}
				if (node->get_banmen()->get_type(x - 1, y) >= EN_HU && node->get_banmen()->get_type(x - 1, y) < EN_OU) {
					scores[1]++;
				}
				if (x < 8 && node->get_banmen()->get_type(x + 1, y) >= EN_HU && node->get_banmen()->get_type(x + 1, y) < EN_OU) {
					scores[1]++;
				}
				if (y >= 1) {
					if (node->get_banmen()->get_type(x - 1, y - 1) >= EN_HU && node->get_banmen()->get_type(x - 1, y - 1) < EN_OU) {
						scores[1]++;
					}
					if (x < 8 && node->get_banmen()->get_type(x + 1, y - 1) >= EN_HU && node->get_banmen()->get_type(x + 1, y - 1) < EN_OU) {
						scores[1]++;
					}
				}

			}

			*/
			counters[node->get_banmen()->get_type(x, y)]++;
		}
	}

	score += (scores[0] << 2);
	score += (scores[1] << 3);

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
*自分の王が自分の陣地内にいれば評価値を返す
*/
int within_ou(BANMEN *banmen) {
	if (banmen->find_koma(EN_OU).get_y() <= 3) return WITHIN_OU;
	return 0;
}

/*
*自分の飛車が自分の陣地内にいれば評価値を返す
*/
int within_hisha(BANMEN *banmen) {
	if (banmen->find_koma(EN_HISHA).get_y() >= 3) return -WITHIN_HISHA;
	return WITHIN_HISHA;
}

/*
*自分の王が自分の陣地内にいれば評価値を返す
*/
int within_kaku(BANMEN *banmen) {
	if (banmen->find_koma(EN_KAKU).get_y() >= 3) return -WITHIN_KAKU;
	return WITHIN_KAKU;
}

/*
*自分の陣地にプレーヤーの駒が入ってくる場合
*/
int within_player(BANMEN *banmen) {
	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 9; x++)
			if (banmen->get_type(x, y) >= HU && banmen->get_type(x, y) <= OU)
				return WITHIN_PLAYER;

	return -WITHIN_PLAYER;
}

/*
*自分の陣地にプレーヤーの駒が入ってくる場合
*/
int num_on_ban(BANMEN *banmen) {
	int count = 0, pl = 0;;
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			if (banmen->get_type(x, y) >= EN_HU && banmen->get_type(x, y) <= EN_OU) {
				count++;
			}
			else if ((banmen->get_type(x, y) >= HU && banmen->get_type(x, y) <= OU)) {
				pl++;
			}
		}
	}


	return (count << 2) - (pl << 2);
}

/*
*盤面上にプレイヤーの飛車(龍も含む)はいるか
*/
int player_hisha(BANMEN *banmen) {
	if (banmen->find_koma(HISHA).get_x() != -1 && banmen->find_koma(RYU).get_x() != -1)
		return 0;
	return PLAYER_HISHA;
}


/*
*盤面上にプレイヤーの角(馬も含む)はいるか
*/
int player_kaku(BANMEN *banmen) {
	if (banmen->find_koma(KAKU).get_x() != -1 && banmen->find_koma(UMA).get_x() != -1)
		return 0;

	return PLAYER_KAKU;
}


/*
*渡された盤面からコンピュータがさせる手をすべてリストアップする関数
*/
void EXPAND(Node *node) {

	/*
       *AIが持ち駒を打つ場合
       */
    u8_t i, koma;
	for (i = 0; i < node->ai_mochigoma->size(); ++i) {
		koma = node->ai_mochigoma->at(i);
		if (koma == EMPTY) {
			continue;
		}
		node->ai_mochigoma->at(i) = EMPTY;

		if (koma == EN_HU) {
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
	
	for (u8_t x = 0; x < 9; ++x) {
		for (u8_t y = 0; y < 9; ++y) {
			if (node->get_banmen()->get_type(x, y) >= EN_HU && node->get_banmen()->get_type(x, y) <= EN_OU) {
                for (Point p : wcm_ftable[node->get_banmen()->get_type(x, y)](node->get_banmen()->get_banmen(), Point(x, y))) {
					BANMEN *new_banmen = new BANMEN;
					new_banmen->copy_banmen(node->get_banmen());

					if (node->get_banmen()->get_type(p.get_x(), p.get_y()) != EMPTY)
					{
						node->ai_mochigoma->push_back(ai_negaeri(node->get_banmen()->get_type(p.get_x(), p.get_y())));
					}

					if (p.get_y() >= 7 && node->get_banmen()->get_type(x, y) >= EN_HU && node->get_banmen()->get_type(x, y) <= EN_KAKU) {
						/*
						*プレイヤーの陣地まで行ったので、成る処理をしたい
						*/
						new_banmen->set_type(p.get_x(), p.get_y(), naru_ftable[node->get_banmen()->get_type(x, y)]());
						new_banmen->set_type(x, y, EMPTY);
						node->get_children()->push_back(new Node(new_banmen, node));
					}
					else {
						/*
						*成る処理は必要ない
						*/
						new_banmen->set_type(p.get_x(), p.get_y(), node->get_banmen()->get_type(x, y));
						new_banmen->set_type(x, y, EMPTY);
						node->get_children()->push_back(new Node(new_banmen, node));
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
	
	u8_t i, koma;
	for (i = 0; i < node->pl_mochigoma->size(); ++i) {
		koma = node->pl_mochigoma->at(i);
		if (koma == EMPTY) {
			continue;
		}
		node->pl_mochigoma->at(i) = EMPTY;

		if (node->pl_mochigoma->at(i) == HU) {
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
			if (node->get_banmen()->get_type(x, y) >= HU && node->get_banmen()->get_type(x, y) <= OU) {
				for (Point p : wcm_ftable[node->get_banmen()->get_type(x, y)](node->get_banmen()->get_banmen(), Point(x, y))) {
					BANMEN *new_banmen = new BANMEN;
					new_banmen->copy_banmen(node->get_banmen());

					if (node->get_banmen()->get_type(p.get_x(), p.get_y()) != EMPTY)
					{
						node->pl_mochigoma->push_back(negaeri(node->get_banmen()->get_type(p.get_x(), p.get_y())));
					}
					
					if (p.get_y() <= 2 && node->get_banmen()->get_type(x, y) >= EN_HU && node->get_banmen()->get_type(x, y) <= EN_KAKU) {
						/*
						*なる必要がある
						*/
						new_banmen->set_type(p.get_x(), p.get_y(), naru_ftable[node->get_banmen()->get_type(x, y)]());
						new_banmen->set_type(x, y, EMPTY);
						node->get_children()->push_back(new Node(new_banmen, node));
					}
					else {
						/*
						*なる必要は無い
						*/
						new_banmen->set_type(p.get_x(), p.get_y(), node->get_banmen()->get_type(x, y));
						new_banmen->set_type(x, y, EMPTY);
						node->get_children()->push_back(new Node(new_banmen, node));
					}
				}
			}

		}
	}
}
