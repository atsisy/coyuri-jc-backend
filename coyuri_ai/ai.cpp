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
}

void CoyuriNegaScout::start()
{
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
		if (this->oute_check(child))
		{
			result = child;
			break;
		}
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

	fprintf(result_file, result->ai_mochigoma->to_string().data());
	printf(result->ai_mochigoma->to_string().data());
	fprintf(result_file, "\n");
	printf("\n");

	fprintf(result_file, "pl_mochi ");
	printf("pl_mochi ");

	fprintf(result_file, result->pl_mochigoma->to_string().data());
	printf(result->pl_mochigoma->to_string().data());
	fprintf(result_file, "\n");
	printf("\n");

	fprintf(result_file, "EVAL %d", this->result->evalue - 10000);
	printf("\nEVAL %d\n", this->result->evalue - 10000);

	fclose(result_file);
}

bool CoyuriNegaScout::oute_check(Node *node) 
{
	u8_t x, y;
	std::vector<Point> points;
	KOMA_TYPE type;
	BANMEN *ban = node->get_banmen();

	for (x = 0; x < 9; ++x) {
		for (y = 0; y < 9; ++y) {
			type = ban->get_type(x, y);
			if (_IS_PLAYER_KOMA(type))
			{
				points = wcm_function_table[_KOMA_TO_INDEX(type)](ban->get_banmen(), point(x, y));
				for (Point p : points) {
					if (p.x == node->ai_ou_point.x && p.y == node->ai_ou_point.y)
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
				points = wcm_function_table[_KOMA_TO_INDEX(type)](ban->get_banmen(), point(x, y));
				for (Point p : points) {
					
					if (p.x == will_reach_point.x && p.y == will_reach_point.y)
					{

						BANMEN *new_banmen = new BANMEN;
						new_banmen->copy_banmen(ban);
						MochiGomaGroup *ai_mochi = root->ai_mochigoma->clone();
						MochiGomaGroup *pl_mochi = root->pl_mochigoma->clone();

						KomaGroup *ai_on_board = root->ai_on_board->clone();
						KomaGroup *pl_on_board = root->pl_on_board->clone();

						new_banmen->set_type(will_reach_point.x, will_reach_point.y, type);
						new_banmen->set_type(x, y, EMPTY);

						ai_on_board->move(_pip_create(x, y, type), _point2d8_create(will_reach_point.x, will_reach_point.y));

						root->get_children().push_back(new Node(new_banmen, root, ai_mochi, pl_mochi, ai_on_board, pl_on_board));
						root->get_children().at(0)->evalue = 10000;
						return;

					}
				}
			}
		}
	}
}