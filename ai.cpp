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
			child->set_evalue(score);
			for (Node *child_child : *child->get_children()) {
				delete child_child;
				child_child = nullptr;
			}
			return score;
		}
		else if (score > score_max) {
			/*
			*beta値を超えていないが、よりよい解が見つかった
			*/
			score_max = score;
			alpha = score;
		}
	}

	for (Node *child_child : *child->get_children()) {
		delete child_child;
		child_child = nullptr;
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
			child->set_evalue(score);
			for (Node *child_child : *child->get_children()) {
				delete child_child;
				child_child = nullptr;
			}
			return score;
		}
		if (score < score_min) {
			/*
			*よりよい解が見つかった
			*/
			score_min = score;
			beta = score;
		}
	}

	for (Node *child_child : *child->get_children()) {
		delete child_child;
		child_child = nullptr;
	}
	return score_min;
}

i64_t nega_scout(Node *node, i64_t alpha, i64_t beta, u8_t depth) {

	if (depth <= 0)
	{
		//printf("%d\n", node->turn);
		return EVAL(node);
	}

	if (_IS_AI_TURN(node->turn))
	{
		EXPAND(node);
	}
	else
	{
		PLAYER_EXPAND(node);
	}

	i64_t score = -100000000, n = beta, value;
	Node *te;

	for (Node *child : *node->get_children())
	{
		value = -nega_scout(child, -n, -std::max(alpha, score), depth - 1);
		child->set_evalue(value);
		if (value > score)
		{
			if (n == beta || depth < 1)
			{
				score = value;
				child->set_evalue(score);
			}
			else
			{
				score = -nega_scout(child, -beta, -value, depth - 1);
				child->set_evalue(score);
			}
		}
		if (score >= beta)
		{
			child->set_evalue(score);
			return score;
		}

		n = std::max(alpha, score) + 1;
	}

	return score;

}

Node *ai_turn(Node *root) {

	//i64_t eval = nega_scout(root, -100000, 100000, 3);
	//i64_t min = 100000000;
	//
	//Node *node = nullptr;

	//for (Node *child : *root->get_children())
	//{
	//	/*if (child->get_evalue() == eval)
	//	{
	//		node = child;
	//		break;
	//	}*/

	//	if (min > child->get_evalue())
	//	{
	//		node = child;
	//	}
	//}


	i64_t eval = max(root, -100000, 100000, 3);
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
