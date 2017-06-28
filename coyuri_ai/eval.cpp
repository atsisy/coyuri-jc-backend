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


static void mochigoma_ai_expand_sub(Node *node, KOMA_TYPE _expand_koma_type);
/*
*渡された盤面からコンピュータがさせる手をすべてリストアップする関数
*/
void EXPAND(Node *node) {

	/*
     *AIが持ち駒を打つ場合
	 */
    u8_t i, size, inner_size, n, x, y;
	KOMA_TYPE koma, may_get_koma;
	PiP pip;
	Point point_regi;
	std::vector<Point> points;
	bool ou_not_found = true;
	BANMEN *new_banmen;
	KomaGroup *new_ai_on_board, *new_pl_on_board;
	
	/*
	*歩の場合は違うwcm関数を使用するため関数化させない
	*/
	size = node->ai_mochigoma->get(EN_HU);
	node->ai_mochigoma->pop(EN_HU);
	for (i = 0; i < size; ++i) {
		points = ai_nihu_wcm(node->get_banmen()->get_banmen());
		for (n = 0; n < points.size(); ++n) {

			//新しい盤面
			new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());
			
			//盤面更新（歩を打つ）
			new_banmen->set_type(points.at(n).x, points.at(n).y, EN_HU);
			
			//盤面上に存在するAIの駒のデータベースを更新
			new_ai_on_board = node->ai_on_board->clone();
			new_ai_on_board->push(_pip_create(points.at(n).x, points.at(n).y, EN_HU));

			//プレイヤー側は確保するだけ
			new_pl_on_board = node->pl_on_board->clone();
			
			node->get_children().push_back(new Node(new_banmen, node, new_ai_on_board, new_pl_on_board));
		}
	}
	node->ai_mochigoma->insert(EN_HU);

	mochigoma_ai_expand_sub(node, EN_KYOUSHA);
	mochigoma_ai_expand_sub(node, EN_KEIMA);
	mochigoma_ai_expand_sub(node, EN_GIN);
	mochigoma_ai_expand_sub(node, EN_KIN);
	mochigoma_ai_expand_sub(node, EN_HISHA);
	mochigoma_ai_expand_sub(node, EN_KAKU);

	for (i = 0, size = node->ai_on_board->size(); i < size; ++i) {

		pip = node->ai_on_board->at(i);
		node->ai_on_board->erase(i);
		koma = _pip_get_type(pip);
		x = _pip_get_x(pip);
		y = _pip_get_y(pip);


		points = wcm_function_table[_KOMA_TO_INDEX(koma)](node->get_banmen()->get_banmen(), point(x, y));
		inner_size = points.size();

		for (n = 0; n < inner_size; ++n) {
			point_regi = points.at(n);
			
			BANMEN *new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());
			
			MochiGomaGroup *ai_mochi = node->ai_mochigoma->clone();
			MochiGomaGroup *pl_mochi = node->pl_mochigoma->clone();

			//プレイヤー側のボードをコピー（AI側の駒が動いた際、プレイヤーのオンボード駒が変化した場合に対応するため）
			new_pl_on_board = node->pl_on_board->clone();

			if (may_get_koma = new_pl_on_board->find_using_xy_and_get_type(point_regi.x, point_regi.y))
			{
				new_pl_on_board->erase(new_pl_on_board->find_pip(_pip_create(point_regi.x, point_regi.y, may_get_koma)));
				ai_mochi->insert(_NEGAERI(may_get_koma));
			}

			if (point_regi.y >= 6) {
				/*
				*プレイヤーの陣地まで行ったので、成る処理をしたい
				*/
				new_banmen->set_type(point_regi.x, point_regi.y, naru_map.at(koma));
				new_banmen->set_type(x, y, EMPTY);

				new_ai_on_board = node->ai_on_board->clone();
				new_ai_on_board->push(_pip_create(x, y, naru_map.at(koma)));

				node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi, new_ai_on_board, new_pl_on_board));
			}
			else {
				/*
				*成る処理は必要ない
				*/
				new_banmen->set_type(point_regi.x, point_regi.y, koma);
				printf("x:y = %d : %d\n", x, y);
				new_banmen->set_type(x, y, EMPTY);

				new_ai_on_board = node->ai_on_board->clone();
				new_ai_on_board->push(_pip_create(x, y, koma));

				node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi, new_ai_on_board, new_pl_on_board));
			}
		}

		node->ai_on_board->set_direct(i, pip);
	}
}

static void mochigoma_ai_expand_sub(Node *node, KOMA_TYPE _expand_koma_type) 
{
	u8_t size, i, n;
	std::vector<Point> points;
	BANMEN *new_banmen;
	KomaGroup *new_ai_on_board, *new_pl_on_board;

	size = node->ai_mochigoma->get(_expand_koma_type);
	node->ai_mochigoma->pop(_expand_koma_type);
	for (i = 0; i < size; ++i) {
		/*
		*point(0, 0)はtegoma_wcmにおいて使用されない。汎用性を持たせるため
		*/
		points = tegoma_wcm(node->get_banmen()->get_banmen(), point(0, 0));
		for (n = 0; n < points.size(); ++n) {

			//新しい盤面
			new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());

			//盤面更新（駒を打つ）
			new_banmen->set_type(points.at(n).x, points.at(n).y, _expand_koma_type);

			//盤面上に存在するAIの駒のデータベースを更新
			new_ai_on_board = node->ai_on_board->clone();
			new_ai_on_board->push(_pip_create(points.at(n).x, points.at(n).y, _expand_koma_type));

			//プレイヤー側は確保するだけ
			new_pl_on_board = node->pl_on_board->clone();

			node->get_children().push_back(new Node(new_banmen, node, new_ai_on_board, new_pl_on_board));
		}
	}
	node->ai_mochigoma->insert(_expand_koma_type);
}

static void mochigoma_pl_expand_sub(Node *node, KOMA_TYPE _expand_koma_type)
{
	u8_t size, i, n;
	std::vector<Point> points;
	BANMEN *new_banmen;
	KomaGroup *new_ai_on_board, *new_pl_on_board;

	size = node->pl_mochigoma->get(_expand_koma_type);
	node->pl_mochigoma->pop(_expand_koma_type);
	for (i = 0; i < size; ++i) {
		/*
		*point(0, 0)はtegoma_wcmにおいて使用されない。汎用性を持たせるため
		*/
		points = tegoma_wcm(node->get_banmen()->get_banmen(), point(0, 0));
		for (n = 0; n < points.size(); ++n) {

			//新しい盤面
			new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());

			//盤面更新（駒を打つ）
			new_banmen->set_type(points.at(n).x, points.at(n).y, _expand_koma_type);

			//盤面上に存在するAIの駒のデータベースを更新
			new_pl_on_board = node->ai_on_board->clone();
			new_pl_on_board->push(_pip_create(points.at(n).x, points.at(n).y, _expand_koma_type));

			//プレイヤー側は確保するだけ
			new_ai_on_board = node->pl_on_board->clone();

			node->get_children().push_back(new Node(new_banmen, node, new_ai_on_board, new_pl_on_board));
		}
	}
	node->pl_mochigoma->insert(_expand_koma_type);
}
/*
*渡された盤面からプレイヤーがさせる手をすべてリストアップする関数
*/
void PLAYER_EXPAND(Node *node) {

	/********************************
	*プレイヤーが持ち駒を打つ場合
	*********************************/
	/*
	*AIが持ち駒を打つ場合
	*/
	u8_t i, size, inner_size, n, x, y;
	KOMA_TYPE koma, may_get_koma;
	PiP pip;
	Point point_regi;
	std::vector<Point> points;
	bool ou_not_found = true;
	BANMEN *new_banmen;
	KomaGroup *new_ai_on_board, *new_pl_on_board;

	/*
	*歩の場合は違うwcm関数を使用するため関数化させない
	*/
	size = node->pl_mochigoma->get(HU);
	node->pl_mochigoma->pop(HU);
	for (i = 0; i < size; ++i) {
		points = ai_nihu_wcm(node->get_banmen()->get_banmen());
		for (n = 0; n < points.size(); ++n) {

			//新しい盤面
			new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());

			//盤面更新（歩を打つ）
			new_banmen->set_type(points.at(n).x, points.at(n).y, HU);

			//盤面上に存在するAIの駒のデータベースを更新
			new_ai_on_board = node->ai_on_board->clone();

			//プレイヤー側は確保するだけ
			new_pl_on_board = node->pl_on_board->clone();
			new_pl_on_board->push(_pip_create(points.at(n).x, points.at(n).y, HU));

			node->get_children().push_back(new Node(new_banmen, node, new_ai_on_board, new_pl_on_board));
		}
	}
	node->pl_mochigoma->insert(HU);

	mochigoma_pl_expand_sub(node, KYOUSHA);
	mochigoma_pl_expand_sub(node, KEIMA);
	mochigoma_pl_expand_sub(node, GIN);
	mochigoma_pl_expand_sub(node, KIN);
	mochigoma_pl_expand_sub(node, HISHA);
	mochigoma_pl_expand_sub(node, KAKU);

	for (i = 0, size = node->pl_on_board->size(); i < size; ++i) {

		pip = node->pl_on_board->at(i);
		node->pl_on_board->erase(i);
		koma = _pip_get_type(pip);
		x = _pip_get_x(pip);
		y = _pip_get_y(pip);

		points = wcm_function_table[_KOMA_TO_INDEX(koma)](node->get_banmen()->get_banmen(), point(x, y));
		inner_size = points.size();

		for (n = 0; n < inner_size; ++n) {
			point_regi = points.at(n);

			BANMEN *new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());

			MochiGomaGroup *ai_mochi = node->ai_mochigoma->clone();
			MochiGomaGroup *pl_mochi = node->pl_mochigoma->clone();

			//AI側のボードをコピー（PL側の駒が動いた際、プレイヤーのオンボード駒が変化した場合に対応するため）
			new_ai_on_board = node->ai_on_board->clone();

			if (may_get_koma = new_ai_on_board->find_using_xy_and_get_type(point_regi.x, point_regi.y))
			{
				new_ai_on_board->erase(new_ai_on_board->find_pip(_pip_create(point_regi.x, point_regi.y, may_get_koma)));
				pl_mochi->insert(_NEGAERI(may_get_koma));
			}

			if (point_regi.y <= 2) {
				/*
				*プレイヤーの陣地まで行ったので、成る処理をしたい
				*/
				new_banmen->set_type(point_regi.x, point_regi.y, naru_map.at(koma));
				new_banmen->set_type(x, y, EMPTY);

				new_pl_on_board = node->pl_on_board->clone();
				new_pl_on_board->push(_pip_create(x, y, naru_map.at(koma)));
				new_pl_on_board->move(pip, _point2d8_create(point_regi.x, point_regi.y));

				node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi, new_ai_on_board, new_pl_on_board));
			}
			else {
				/*
				*成る処理は必要ない
				*/
				new_banmen->set_type(point_regi.x, point_regi.y, koma);
				new_banmen->set_type(x, y, EMPTY);

				new_pl_on_board = node->pl_on_board->clone();
				new_pl_on_board->push(_pip_create(x, y, koma));
				new_pl_on_board->move(pip, _point2d8_create(point_regi.x, point_regi.y));

				node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi, new_ai_on_board, new_pl_on_board));
			}
		}

		node->pl_on_board->set_direct(i, pip);
	}
}
