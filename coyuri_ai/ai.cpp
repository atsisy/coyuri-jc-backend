#include "types.hpp"
#include "prot.hpp"
#include "values.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>


extern std::function<std::vector<Point>(KOMA_TYPE **, Point)> wcm_function_table[29];

/*
*探索部分
*探索の深さは2手先まで
*/
i64_t max(Node *node, i64_t alpha, i64_t beta, u8_t limit) {

	if (limit <= 0) {
		/*
		*一番深いノードまで達した
		*/
		return EVAL(node);
	}

	i64_t score = 0, score_max = -10000000;
	u64_t size;
	Node *te = nullptr, *child = nullptr;

	//可能な手を生成
	EXPAND(node);

	size = node->get_children().size();
	for (u64_t i = 0; i < size; ++i)
	{
		child = node->get_children().at(i);
		score = min(child, alpha, beta, limit - 1);
		child->set_evalue(score);

		if (score >= beta) {
			/*
			*beta値より大きくなった場合
			*/
			child->delete_children();
			return score;
		}
		else if (score > score_max) {
			/*
			*beta値を超えていないが、よりよい解が見つかった
			*/
			score_max = score;
			alpha = score;
		}
		child->delete_children();
	}

	return score_max;
}

i64_t min(Node *node, i64_t alpha, i64_t beta, u8_t limit) {

	if (limit <= 0) {
		/*
		*一番深いノードまで達した
		*/
		return EVAL(node);
	}

	i64_t score = 0, score_min = 100000000;
	u64_t size;
	Node *te = nullptr, *child = nullptr;

	//可能な手を生成
	PLAYER_EXPAND(node);

	size = node->get_children().size();
	for (u64_t i = 0; i < size; ++i)
	{
		child = node->get_children().at(i);
		score = max(child, alpha, beta, limit - 1);
		child->set_evalue(score);

		if (score <= alpha) {
			/*
			*alpha値より小さくなった場合
			*/
			child->delete_children();
			return score;
		}
		if (score < score_min) {
			/*
			*よりよい解が見つかった
			*/
			score_min = score;
			beta = score;
		}

		child->delete_children();
	}

	return score_min;
}

//
//i64_t negascout(Node *node, i64_t alpha, i64_t beta, u8_t limit)
//{
//	if (!limit) {
//		return EVAL(node); // 深さ制限に達した
//	}
//
//
//	u8_t i, size;
//	i64_t a, b, te_score, score_max = -10000000;
//	Node *child;
//	a = alpha;
//	b = beta;
//
//	if (_IS_AI_TURN(node->turn))
//	{
//		EXPAND(node);
//
//		for (i = 0, size = node->get_children().size(); i < size; ++i) {
//			node->get_children().at(i)->set_evalue(EVAL(node->get_children().at(i)));
//		}
//		std::sort(node->get_children().begin(), node->get_children().end(), &Node::compare_1_bigger_than_2);
//	}
//	else
//	{
//		PLAYER_EXPAND(node);
//		for (i = 0, size = node->get_children().size(); i < size; ++i) {
//			node->get_children().at(i)->set_evalue(EVAL(node->get_children().at(i)));
//		}
//		std::sort(node->get_children().begin(), node->get_children().end(), &Node::compare_1_less_than_2);
//	}
//
//	for (i = 0, size = node->get_children().size(); i < size; ++i) {
//		child = node->get_children().at(i);
//		//手を打つ;
//		te_score = -negascout(child, -b, -a, limit - 1);
//		child->set_evalue(te_score);
//
//		if (te_score > a && te_score < beta && i != 0 && limit > 2) {
//			/*
//			* 再探索
//			*/
//			te_score = -negascout(child, -beta, -te_score, limit - 1);
//			child->set_evalue(te_score);
//		}
//
//		if (te_score > score_max) {
//			if (te_score >= beta) 
//			{
//				child->delete_children();
//				return te_score; // β刈り
//			}
//			score_max = te_score;
//			a = a > te_score ? a : te_score;
//		}
//
//		b = a + 1; // 新しい null windowを設定
//
//		child->delete_children();
//	}
//
//	return score_max;
//}

i64_t CoyuriNegaScout::nega_scout_search(Node *node, i64_t alpha, i64_t beta, u8_t limit)
{
	if (!limit) {
		return this->eval(node); // 深さ制限に達した
	}


	u8_t i, size;
	i64_t a, b, te_score, score_max = -10000000;
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
		this->eval = early_eval_function;
	}
	else
	{
		this->eval = EVAL;
	}
}

void CoyuriNegaScout::start()
{
	i64_t e_value = nega_scout_search(root, -100000, 100000, 4);

	std::sort(std::begin(root->get_children()), std::end(root->get_children()), &CoyuriNegaScout::compare_1_bigger_than_2);

	for (Node *child : root->get_children())
	{
		if (this->oute_check(child->get_banmen()))
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

	fclose(result_file);
}

bool CoyuriNegaScout::oute_check(BANMEN *ban) 
{
	u8_t x, y;
	std::vector<Point> points;
	KOMA_TYPE type;

	Point ou_point;
	for (x = 0; x < 9; ++x) {
		for (y = 0; y < 9; ++y) {
			if (ban->get_type(x, y) == EN_OU) {
				ou_point = point(x, y);
			}
			
		}
	}
	for (x = 0; x < 9; ++x) {
		for (y = 0; y < 9; ++y) {
			type = ban->get_type(x, y);
			if (_IS_PLAYER_KOMA(type))
			{
				points = wcm_function_table[_KOMA_TO_INDEX(type)](ban->get_banmen(), point(x, y));
				for (Point p : points) {
					if (p.x == ou_point.x && p.y == ou_point.y)
					{
						return false;
					}
				}
			}
		}
	}

	return true;
}