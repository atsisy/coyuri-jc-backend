#include "types.hpp"
#include "prot.hpp"
#include "coutil.hpp"
#include "values.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <thread>
#include <mutex>

//#define _ENABLE_TSUME

extern std::function<std::vector<Point>(KOMA_TYPE **, Point)> wcm_function_table[29];

i64_t CoyuriNegaScout::nega_scout_search(Node *node, i64_t alpha, i64_t beta, u8_t limit)
{
	if (!limit) {
		return this->eval(node); // 深さ制限に達した
	}

	u8_t i, size;
	i64_t a, b, te_score, score_max = _NGST_SEARCH_INIT_SCORE_MAX_VALUE;
	Node *child;
	a = alpha;
	b = beta;

	if (_IS_AI_TURN(node->turn))
	{
		EXPAND(node);

		for (i = 0, size = node->get_children().size(); i < size; ++i) {
			node->get_children().at(i)->set_evalue(this->eval(node->get_children().at(i)));
		}
		std::sort(node->get_children().begin(), node->get_children().end(), &CoyuriNegaScout::compare_1_bigger_than_2);
	}
	else
	{
		PLAYER_EXPAND(node);
		for (i = 0, size = node->get_children().size(); i < size; ++i) {
			node->get_children().at(i)->set_evalue(this->eval(node->get_children().at(i)));
		}
		std::sort(node->get_children().begin(), node->get_children().end(), &CoyuriNegaScout::compare_1_less_than_2);
	}

	for (i = 0, size = node->get_children().size(); i < size; ++i) {
		child = node->get_children().at(i);
		//手を打つ;
		te_score = -nega_scout_search(child, -b, -a, limit - 1);
		child->set_evalue(te_score);

		if (te_score > a && te_score < beta && i != 0 && limit > 2) {
			/*
			* 再探索
			*/
			te_score = -nega_scout_search(child, -beta, -te_score, limit - 1);
			child->set_evalue(te_score);
		}

		if (te_score > score_max) {
			if (te_score >= beta)
			{
				child->delete_children();
				return te_score; // β刈り
			}
			score_max = te_score;
			a = a > te_score ? a : te_score;
		}

		b = a + 1; // 新しい null windowを設定

		child->delete_children();
	}

	return score_max;
}

CoyuriNegaScout::CoyuriNegaScout(Node *node, u64_t tesuu)
{
	this->root = node;
	this->result = nullptr;
	this->tesuu = tesuu;

	if (tesuu < 10)
	{
		this->search_depth = SEARCH_DEPTH;
		this->eval = early_eval_function;
	}
	else if (tesuu > 55)
	{
		this->search_depth = SEARCH_DEPTH;
		this->eval = late_eval_function;
	}
	else
	{
		this->search_depth = SEARCH_DEPTH;
		this->eval = EVAL;
	}

	main_search_fin = false;
	tsumi_check_fin = false;

}

void CoyuriNegaScout::start()
{

	if (this->tesuu <= 1)
	{
		this->use_first_jouseki();
		result = root->get_children().front();
		return;
	}


#ifdef _ENABLE_TSUME
	Node *tsumi_check;

	std::thread tsumi_check_thread([&] {
		tsumi_check = this->pl_ou_tsumi_check();
		while (!this->ref_main_search_fin()) {
			std::this_thread::sleep_for(std::chrono::microseconds(100));
		}
	});
#endif

	i64_t e_value = nega_scout_search(root, -100000, 100000, this->search_depth);

	std::sort(std::begin(root->get_children()), std::end(root->get_children()), &CoyuriNegaScout::compare_1_bigger_than_2);

	for (Node *child : root->get_children())
	{
		if (this->ai_en_oute_check(child))
		{
			result = child;
			break;
		}
	}

#ifdef _ENABLE_TSUME

	this->ref_main_search_fin() = true;
	tsumi_check_thread.join();

	if (tsumi_check == nullptr)
	{
		/*
		*詰んでいない
		*/
	}
	else
	{
		e_value = tsumi_check->get_evalue();
		/*
		*詰んだ
		*/
		if (tsumi_check->get_parent() == nullptr) {
			/*
			*ルートノードで詰んでいた場合
			*/
			this->result = tsumi_check;
			return;
		}
		while (tsumi_check->get_parent()->get_parent() != nullptr) {
			/*
			*詰みに到達するノードの祖先ノードの子ノードまでループ
			*/
			tsumi_check = tsumi_check->get_parent();
		}
		this->result = tsumi_check;

		this->result->set_evalue(e_value);

		return;
	}

#endif

}

void CoyuriNegaScout::print(const char *file_name)
{
	FILE *result_file = fopen(file_name, "w");

	for (u8_t y = 0; y < 9; y++) {
		for (u8_t x = 0; x < 9; ++x) {
			if (_IS_EMPTY(result->get_banmen()->get_banmen()[x][y]))
			{
				fprintf(result_file, "0 ");
				printf("0 ");
			}
			else {
				fprintf(result_file, "%d ", (result->get_banmen()->get_banmen()[x][y] >> 1) + 1);
				printf("%d ", (result->get_banmen()->get_banmen()[x][y] >> 1) + 1);
			}
		}
		fprintf(result_file, "\n");
		printf("\n");
	}

	fprintf(result_file, "ai_mochi ");
	printf("ai_mochi ");
	for (KOMA_TYPE type : *result->ai_mochigoma) {
		if (!type) {
			continue;
		}
		fprintf(result_file, "%d ", (type >> 1) + 1);
		printf("%d ", (type >> 1) + 1);
	}
	fprintf(result_file, "\n");
	printf("\n");

	fprintf(result_file, "pl_mochi ");
	printf("pl_mochi ");
	for (KOMA_TYPE type : *result->pl_mochigoma) {
		if (!type) {
			continue;
		}
		fprintf(result_file, "%d ", (type >> 1) + 1);
		printf("%d ", (type >> 1) + 1
		);
	}
	fprintf(result_file, "\n");
	
	/*
	*評価値補正
	*/
	if (this->tesuu <= 1)
	{
		fprintf(result_file, "EVAL %d", 0);
		printf("\nEVAL %d\n", 0);
	}
	else if (this->tesuu < 10)
	{
		fprintf(result_file, "EVAL %I64d", this->result->evalue + 5872);
		printf("\nEVAL %I64d\n", this->result->evalue + 5872);
	}
	else if (this->tesuu > 55) {
		fprintf(result_file, "EVAL %I64d", this->result->evalue + 6336);
		printf("\nEVAL %I64d\n", this->result->evalue + 6336);
	}
	else
	{
		fprintf(result_file, "EVAL %I64d", this->result->evalue + 6000);
		printf("\nEVAL %I64d\n", this->result->evalue + 6000);
	}

	fclose(result_file);
}

bool CoyuriNegaScout::ai_en_oute_check(Node *node) 
{
	u8_t x, y, i, size;
	std::vector<Point> points;
	KOMA_TYPE type;
	BANMEN *ban = node->get_banmen();

	for (x = 0; x < 9; ++x) {
		for (y = 0; y < 9; ++y) {
			type = ban->get_type(x, y);
			if (_IS_PLAYER_KOMA(type))
			{
				points = wcm_function_table[_KOMA_TO_INDEX(type)](ban->get_banmen(), Point(x, y));
				for (i = 0, size = points.size(); i < size; ++i) {
					if (points.at(i).x == node->ai_ou_point.x && points.at(i).y == node->ai_ou_point.y)
					{
						return false;
					}
				}
			}
		}
	}

	return true;
}

bool CoyuriNegaScout::pl_oute_check(Node *node)
{
	u8_t x, y, i, size;
	std::vector<Point> points;
	KOMA_TYPE type;
	BANMEN *ban = node->get_banmen();

	for (x = 0; x < 9; ++x) {
		for (y = 0; y < 9; ++y) {
			type = ban->get_type(x, y);
			if (_IS_AI_KOMA(type))
			{
				points = wcm_function_table[_KOMA_TO_INDEX(type)](ban->get_banmen(), Point(x, y));
				for (i = 0, size = points.size(); i < size; ++i) {
					if (points.at(i).x == node->pl_ou_point.x && points.at(i).y == node->pl_ou_point.y)
					{
						return false;
					}
				}
			}
		}
	}

	return true;
}

void CoyuriNegaScout::use_first_jouseki()
{

	cut::Jouseki jouseki("C:\\Users\\Akihiro\\Desktop\\first_jouseki.json");
	Te te = jouseki.jouseki_list.at(0);
	BANMEN *ban = root->get_banmen();
	KOMA_TYPE type;
	Point will_reach_point(te.gone_x, te.gone_y);
	std::vector<Point> points;

	u8_t x = te.from_x, y = te.from_y;

	type = ban->get_type(x, y);
	points = wcm_function_table[_KOMA_TO_INDEX(type)](ban->get_banmen(), Point(x, y));
	for (Point p : points) {

		if (p.x == will_reach_point.x && p.y == will_reach_point.y)
		{

			BANMEN *new_banmen = new BANMEN;
			new_banmen->copy_banmen(ban);
			MochiGoma *ai_mochi = clone_mochigoma(root->ai_mochigoma);
			MochiGoma *pl_mochi = clone_mochigoma(root->pl_mochigoma);

			new_banmen->set_type(will_reach_point.x, will_reach_point.y, type);
			new_banmen->set_type(x, y, EMPTY);
			root->get_children().push_back(new Node(new_banmen, root, ai_mochi, pl_mochi));
			root->get_children().at(0)->evalue = 10000;
			return;

		}
	}
}

Node *CoyuriNegaScout::pl_ou_tsumi_check(Node *clone_root) {

	Node *work;
	u8_t i, size;
	std::vector<Node *> node_queue;
	node_queue.push_back(clone_root);
	u16_t turn = 0;
	std::vector<Node *> cache;

	while (node_queue.size()) {

		if (!(turn % 2))
		{

			for(i = 0, size = node_queue.size();i < size;++i) {
				work = node_queue.at(i);

				EXPAND(work);

				//王手がかかっているか
				for (Node *node : work->get_children()) {
					if (!this->pl_oute_check(node)) {
						/*
						*かかっている
						*/
						cache.push_back(node);
					}
					else
					{
						/*
						*かけられていない
						*/
						delete node;
					}
				}
			}
			/*
			*古いノードをすべて削除
			*/
			node_queue.clear();

			if (!cache.size())
			{
				/*
				*王手をかけられなかった。探索終了
				*/
				return nullptr;
			}

			for (Node *node : cache) {
				/*
				*王手を欠けることに成功したノードを入れる
				*/
				node_queue.push_back(node);
			}

			/*
			*一時的に王手ノードをためて
			*/
			cache.clear();

		}
		else
		{
			std::vector<std::vector<Node *>> cache_vector;
			for(i = 0, size = node_queue.size();i < size; ++i) 
			{
				work = node_queue.at(i);

				PLAYER_EXPAND(work);
				Node *fin_node;
				//王手を回避できていなければ詰み
				for (Node *node : work->get_children())
				{
					if (this->pl_oute_check(node)) {
						/*
						*王手じゃない手だった->回避したのでもう一層深く
						*/		
						cache.push_back(node);

					}
					else
					{
						fin_node = node;
						//delete node;
					}
				}

				if (!cache.size())
				{
					/*
					*詰んだ!!
					*/
					/*
					*アイデアメモ
					*詰み筋が発見されたら、この手順をファイル等に吐く。本探索は行わず、それを読んで対局
					*/

					//一時的にworkを返しておくが、もっときれいに書ける
					work->set_evalue(999999);

					return work;
				}
				else if(cache.size() <= 0)
				{
					/*
					*詰みを避ける方法が2通り以下のみ探索続行
					*/
					for (Node *node : cache) {
						node->set_evalue(EVAL(node));
					}
					std::sort(cache.begin(), cache.end(), &CoyuriNegaScout::compare_1_less_than_2);
					
					cache_vector.push_back(cache);
				}

				cache.clear();

			}

			node_queue.clear();
			for (std::vector<Node *> vec : cache_vector) {
				for (Node *node : vec) {
					node_queue.push_back(node);
				}
			}
		}

		++turn;
	}

	return nullptr;
}

void CoyuriNegaScout::start_onboard_search(Node **result_node_box)
{
	std::vector<Node *> ans_cancy;
	i64_t max_evalue, count;

	Node *main_search_root = this->root->clone();

	this->nega_scout_search_f_onboard(main_search_root, -100000, 100000, this->search_depth);

	std::sort(std::begin(main_search_root->get_children()), std::end(main_search_root->get_children()), &CoyuriNegaScout::compare_1_bigger_than_2);

	for (Node *child : main_search_root->get_children())
	{
		if (this->ai_en_oute_check(child))
		{
			if (std::abs(child->evalue) != std::abs(_NGST_SEARCH_INIT_SCORE_MAX_VALUE))
			{
				/*
				* 誤って混入したいい手の候補を取り除く
				*/
				ans_cancy.push_back(child);

			}
		}
	}

	max_evalue = ans_cancy.front()->get_evalue();
	for (count = 0; count < ans_cancy.size(); ++count)
	{
		if (ans_cancy.at(count)->get_evalue() != max_evalue)
		{
			break;
		}
	}

	ans_cancy.resize(count);
	for (Node *child : ans_cancy) {
		child->set_evalue(this->eval(child));
	}
	std::sort(std::begin(ans_cancy), std::end(ans_cancy), &CoyuriNegaScout::compare_1_bigger_than_2);
	*result_node_box = ans_cancy.front();

	while (!this->ref_main_search_fin()) {
		std::this_thread::sleep_for(std::chrono::microseconds(100));
	}
}

void CoyuriNegaScout::start_tsumi_check(Node **result_node_box)
{
	i64_t e_value;

	Node *tsumi_check_root = this->root->clone();
	Node *tsumi_check = this->pl_ou_tsumi_check(tsumi_check_root);

	if (tsumi_check == nullptr)
	{
		/*
		*詰んでいない
		*/
		*result_node_box = nullptr;
	}
	else
	{
		e_value = tsumi_check->get_evalue();
		/*
		*詰んだ
		*/
		if (tsumi_check->get_parent() == nullptr) {
			/*
			*ルートノードで詰んでいた場合
			*/
			*result_node_box = tsumi_check;
		}
		else {
			while (tsumi_check->get_parent()->get_parent() != nullptr) {
				/*
				*詰みに到達するノードの祖先ノードの子ノードまでループ
				*/
				tsumi_check = tsumi_check->get_parent();
			}
			*result_node_box = tsumi_check;
		}
		(*result_node_box)->set_evalue(e_value);
	}
	
	while (!this->ref_tsumi_check_fin()) {
		std::this_thread::sleep_for(std::chrono::microseconds(100));
	}

}

void CoyuriNegaScout::dual_thread_start()
{

	if (this->tesuu <= 1)
	{
		this->use_first_jouseki();
		result = root->get_children().front();
		return;
	}

	Node *main_search_result, *tsumi_check_result;
	i64_t mochigoma_search_e_value, onboard_search_evalue;

	std::thread main_search_thread(&CoyuriNegaScout::start_onboard_search, this, &main_search_result);
	std::thread tsumi_check_thread(&CoyuriNegaScout::start_tsumi_check, this, &tsumi_check_result);

	nega_scout_search_f_mochigoma(root, -100000, 100000, this->search_depth);

	/*
	*本探索と詰みチェッカに終了許可を出す
	*/
	this->ref_tsumi_check_fin() = true;
	tsumi_check_thread.join();
	this->ref_main_search_fin() = true;
	main_search_thread.join();
	
	std::sort(std::begin(root->get_children()), std::end(root->get_children()), &CoyuriNegaScout::compare_1_bigger_than_2);

	for (Node *child : root->get_children())
	{
		if (this->ai_en_oute_check(child))
		{
			if (std::abs(child->evalue) != std::abs(_NGST_SEARCH_INIT_SCORE_MAX_VALUE))
			{
				/*
				* 誤って混入したいい手の候補を取り除く
				*/
				this->result = child;
				mochigoma_search_e_value = this->result->get_evalue();
				break;
			}
		}
	}

	/**************
	*ここから解選択
	****************************************************************/

	if (tsumi_check_result != nullptr)
	{
		/*
		*詰み筋を見つけた
		*/
		if (this->ai_en_oute_check(tsumi_check_result)) {
			this->result = tsumi_check_result;
			return;
		}
	}

	/*
	*持ち駒が無い
	*/
	if (!root->get_children().size())
	{
		/*
		*盤面上の結果を入れてすぐに戻る
		*/
		this->result = main_search_result;
		return;
	}

	onboard_search_evalue = main_search_result->get_evalue();
	
	if (mochigoma_search_e_value > onboard_search_evalue && this->result != nullptr)
	{
		/*
		*持ち駒の探索結果の方が良かった
		*/
		result->set_evalue(mochigoma_search_e_value);
		delete main_search_result;
	}
	else
	{
		/*
		*盤面上の探索結果の方が良かった
		*/
		this->result = main_search_result;
		this->result->set_evalue(onboard_search_evalue);
	}

	return;

}

i64_t CoyuriNegaScout::nega_scout_search_f_onboard(Node *node, i64_t alpha, i64_t beta, u8_t limit)
{
	if (!limit) {
		return this->eval(node); // 深さ制限に達した
	}

	u8_t i, size;
	i64_t a, b, te_score, score_max = _NGST_SEARCH_INIT_SCORE_MAX_VALUE;
	Node *child;
	a = alpha;
	b = beta;

	if (_IS_AI_TURN(node->turn))
	{
		/*
		*AIのターンのときのノード展開
		*初期ノード展開は盤上のみ。もう一つのスレッドで持ち駒を展開する。
		*/
		if (limit == this->search_depth)
		{
			AI_EXPAND_ONLY_ON_BOARD(node);
		}
		else {
			EXPAND(node);
		}

		for (i = 0, size = node->get_children().size(); i < size; ++i) {
			node->get_children().at(i)->set_evalue(this->eval(node->get_children().at(i)));
		}
		std::sort(node->get_children().begin(), node->get_children().end(), &CoyuriNegaScout::compare_1_bigger_than_2);
	}
	else
	{
		/*
		*プレイヤーのターンのときのノード展開
		*初期ノード展開は盤上のみ。もう一つのスレッドで持ち駒を展開する。
		*/

		PLAYER_EXPAND(node);

		for (i = 0, size = node->get_children().size(); i < size; ++i) {
			node->get_children().at(i)->set_evalue(this->eval(node->get_children().at(i)));
		}
		std::sort(node->get_children().begin(), node->get_children().end(), &CoyuriNegaScout::compare_1_less_than_2);
	}

	for (i = 0, size = node->get_children().size(); i < size; ++i) {
		child = node->get_children().at(i);
		
		te_score = -nega_scout_search(child, -b, -a, limit - 1);
		child->set_evalue(te_score);

		if (te_score > a && te_score < beta && i != 0 && limit > 2) {
			/*
			* 再探索
			*/
			te_score = -nega_scout_search(child, -beta, -te_score, limit - 1);
			child->set_evalue(te_score);
		}

		if (te_score > score_max) {
			if (te_score >= beta)
			{
				child->delete_children();
				return te_score;
			}
			score_max = te_score;
			a = a > te_score ? a : te_score;
		}

		b = a + 1;

		child->delete_children();
	}

	return score_max;
}

i64_t CoyuriNegaScout::nega_scout_search_f_mochigoma(Node *node, i64_t alpha, i64_t beta, u8_t limit)
{
	if (!limit) {
		return this->eval(node);
	}

	u8_t i, size;
	i64_t a, b, te_score, score_max = _NGST_SEARCH_INIT_SCORE_MAX_VALUE;
	Node *child;
	a = alpha;
	b = beta;

	if (_IS_AI_TURN(node->turn))
	{
		/*
		*AIのターンのときのノード展開
		*初期ノード展開は盤上のみ。もう一つのスレッドで持ち駒を展開する。
		*/
		if (limit == this->search_depth)
		{
			AI_EXPAND_ONLY_MOCHIGOMA(node);
		}
		else {
			EXPAND(node);
		}

		for (i = 0, size = node->get_children().size(); i < size; ++i) {
			node->get_children().at(i)->set_evalue(this->eval(node->get_children().at(i)));
		}
		std::sort(node->get_children().begin(), node->get_children().end(), &CoyuriNegaScout::compare_1_bigger_than_2);
	}
	else
	{
		/*
		*プレイヤーのターンのときのノード展開
		*初期ノード展開は盤上のみ。もう一つのスレッドで持ち駒を展開する。
		*/

		PLAYER_EXPAND(node);

		for (i = 0, size = node->get_children().size(); i < size; ++i) {
			node->get_children().at(i)->set_evalue(this->eval(node->get_children().at(i)));
		}
		std::sort(node->get_children().begin(), node->get_children().end(), &CoyuriNegaScout::compare_1_less_than_2);
	}

	for (i = 0, size = node->get_children().size(); i < size; ++i) {
		child = node->get_children().at(i);

		te_score = -nega_scout_search(child, -b, -a, limit - 1);
		child->set_evalue(te_score);

		if (te_score > a && te_score < beta && i != 0 && limit > 2) {
			/*
			* 再探索
			*/
			te_score = -nega_scout_search(child, -beta, -te_score, limit - 1);
			child->set_evalue(te_score);
		}

		if (te_score > score_max) {
			if (te_score >= beta)
			{
				child->delete_children();
				return te_score; // β刈り
			}
			score_max = te_score;
			a = a > te_score ? a : te_score;
		}

		b = a + 1;

		child->delete_children();
	}

	return score_max;
}