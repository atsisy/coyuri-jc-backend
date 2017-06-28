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

extern std::function<std::vector<Point>(KOMA_TYPE **, Point)> wcm_function_table[29];

i64_t CoyuriNegaScout::nega_scout_search(Node *node, i64_t alpha, i64_t beta, u8_t limit)
{
	if (!limit) {
		return this->eval(node); // 深さ制限に達した
	}

	u8_t i, size;
	i64_t a, b, te_score, score_max = -1000000;
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
		this->search_depth = 4;
		this->eval = early_eval_function;
	}
	else
	{
		this->search_depth = 4;
		this->eval = EVAL;
	}

	main_search_fin = false;

}

void CoyuriNegaScout::start()
{
	Node *tsumi_check;
	
	std::thread tsumi_check_thread([&] {
		tsumi_check = this->pl_ou_tsumi_check();
		while (!this->ref_main_search_fin()) {
			std::this_thread::sleep_for(std::chrono::microseconds(100));
		}
	});

	if (this->tesuu <= 1)
	{
		this->use_first_jouseki();
		result = root->get_children().front();
		return;
	}
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
		/*
		*詰んだ
		*/
	}

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
	fprintf(result_file, "EVAL %d", this->result->evalue - 10000);

	printf("\nEVAL %d\n", this->result->evalue - 10000);

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
			if (_IS_PLAYER_KOMA(type))
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
	cut::Te te = jouseki.jouseki_list.at(0);
	BANMEN *ban = root->get_banmen();
	KOMA_TYPE type = te.type;
	Point will_reach_point = te.point;
	std::vector<Point> points;

	u8_t x, y;

	for (x = 0; x < 9; ++x) {
		for (y = 0; y < 9; ++y) {
			if (_EQUALS(ban->get_type(x, y), type))
			{
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
		}
	}
}

Node *CoyuriNegaScout::pl_ou_tsumi_check() {
	Node *clone_root = this->root->clone();
	Node *work;
	std::queue<Node *> node_queue;
	node_queue.push(clone_root);
	u16_t turn = 0;
	std::vector<Node *> cache;

	while (node_queue.size()) {

		if (!(turn % 2))
		{

			while (node_queue.size()) {

				work = node_queue.front();
				node_queue.pop();

				EXPAND(work);

				//王手がかかっているか
				for (Node *node : work->get_children()) {
					if (!this->pl_oute_check(work)) {
						/*
						*かかっている
						*/
						cache.push_back(node);
					}
				}
			}

			if (!cache.size())
			{
				/*
				*王手をかけられなかった。探索終了
				*/
				break;
			}

			for (Node *node : cache) {
				node_queue.push(node);
			}

			cache.clear();

		}
		else
		{
			while (node_queue.size()) {

				work = node_queue.front();
				node_queue.pop();

				PLAYER_EXPAND(work);

				//王手を回避できていなければ詰み
				for (Node *node : work->get_children()) {
					if (this->pl_oute_check(work)) {
						/*
						*王手じゃない手だった->回避したのでもう一層深く
						*/		
						cache.push_back(node);

					}
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
				return work;
			}

			for (Node *node : cache) {
				node_queue.push(node);
			}

			cache.clear();
		}

		++turn;
	}

	return nullptr;
}