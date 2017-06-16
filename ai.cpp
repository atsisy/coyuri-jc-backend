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
Node *max(Node *node, int alpha, int beta, int limit) {

	if (limit <= 0) {
		/*
		*一番深いノードまで達した
		*/
		node->set_evalue(EVAL(node));
		return node;
	}

	int score = 0, score_max = -10000;
	u64_t size;
	
	Node *te = NULL, *iti = NULL;
	//可能な手を生成
	EXPAND(node);

	size = (*node->get_children()).size();
	for (u64_t i = 0; i < size; ++i) {
		//score = min((*node->get_children()).at(i), alpha, beta, limit-1)->get_evalue();
		iti = min((*node->get_children()).at(i), alpha, beta, limit - 1);
		score = iti->get_evalue();
		if (score >= beta) {
			/*
			*beta値より大きくなった場合
			*/
			(*node->get_children()).at(i)->set_evalue(score);
			for (u64_t n = i + 1; n < (*node->get_children()).size(); ++n) {
				delete (*node->get_children()).at(n);
				(*node->get_children()).at(n) = nullptr;
			}
			delete te;
			te = nullptr;
			delete iti;
			iti = nullptr;
			return (*node->get_children()).at(i);
		}
		if (score > score_max) {
			/*
			*よりよい解が見つかった
			*/
			delete te;
			te = (*node->get_children()).at(i);
			te->set_evalue(score);
			score_max = score;
			alpha = score;
		}
		else {
			delete (*node->get_children()).at(i);
			(*node->get_children()).at(i) = nullptr;
		}
		//delete iti;
	}

	return te;
}

Node *min(Node *node, int alpha, int beta, int limit) {

	if (limit <= 0) {
		/*
		*一番深いノードまで達した
		*/
		node->set_evalue(EVAL(node));
		return node;
	}

	int score = 0, score_max = 10000;
	Node *te = NULL;
	//可能な手を生成
	PLAYER_EXPAND(node);

	for (u64_t i = 0; i < (*node->get_children()).size(); ++i) {
		score = max((*node->get_children()).at(i), alpha, beta, limit - 1)->get_evalue();
		//iti = max((*node->get_childrﾎﾞｿｯen()).at(i), alpha, beta, limit-1);
		//score = iti->get_evalue();
		if (score <= alpha) {
			/*
			*alpha値より小さくなった場合
			*/
			(*node->get_children()).at(i)->set_evalue(score);
			for (u64_t n = i + 1; n < (*node->get_children()).size(); ++n) {
				delete (*node->get_children()).at(n);
				(*node->get_children()).at(n) = nullptr;
			}
			delete te;
			return (*node->get_children()).at(i);
		}
		if (score < score_max) {
			/*
			*よりよい解が見つかった
			*/
			delete te;
			te = (*node->get_children()).at(i);
			te->set_evalue(score);
			score_max = score;
			beta = score;
		}
		else {
			delete (*node->get_children()).at(i);
			(*node->get_children()).at(i) = nullptr;
		}
		//delete iti;
	}

	return te;
}

Node *nega_scout(Node *node, i64_t alpha, i64_t beta, u8_t depth) {

	if (depth <= 0)
	{
		node->set_evalue(EVAL(node));
		return node;
	}
		
}

Node *ai_turn(Node *root) {

	Node *node = max(root, -100000, 100000, 3);
	
	return node;
}
