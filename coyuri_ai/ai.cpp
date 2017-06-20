#include "types.hpp"
#include "prot.hpp"
#include "values.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

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

	size = (*node->get_children()).size();
	for (u64_t i = 0; i < size; ++i)
	{
		child = (*node->get_children()).at(i);
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

	size = (*node->get_children()).size();
	for (u64_t i = 0; i < size; ++i)
	{
		child = (*node->get_children()).at(i);
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

i64_t negascout(Node *node, i64_t alpha, i64_t beta, u8_t limit)
{
	if (!limit) {
		return EVAL(node); // 深さ制限に達した
	}

	if (_IS_AI_TURN(node->turn))
	{
		EXPAND(node);
		for (Node *n : *node->get_children()) {
			n->set_evalue(EVAL(n));
		}
		std::sort(node->get_children()->begin(), node->get_children()->end(), &Node::compare_1_bigger_than_2);
	}
	else
	{
		PLAYER_EXPAND(node);
		for (Node *n : *node->get_children()) {
			n->set_evalue(EVAL(n));
		}
		std::sort(node->get_children()->begin(), node->get_children()->end(), &Node::compare_1_less_than_2);
	}

	u8_t i, size;
	i64_t a, b, te_score, score_max = -10000000;
	Node *child;
	a = alpha;
	b = beta;

	for (i = 0, size = node->get_children()->size(); i < size; ++i) {
		child = node->get_children()->at(i);
		//手を打つ;
		te_score = -negascout(child, -b, -a, limit - 1);
		child->set_evalue(te_score);

		if (te_score > a && te_score < beta && i != 0 && limit > 2) {
			/*
			* 再探索
			*/
			te_score = -negascout(child, -beta, -te_score, limit - 1);
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

Node *ai_turn(Node *root) {

	i64_t eval = negascout(root, -100000, 100000, 4);
	Node *node = nullptr;

	for (Node *child : *root->get_children())
	{
		if (child->get_evalue() == eval)
		{
			node = child;
			break;
		}
	}
	
	return node;
}
