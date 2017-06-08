#include "types.hpp"
#include "prot.hpp"
#include "values.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

KOMA_TYPE **ban;

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
	Node *te = NULL, *iti = NULL;
	//可能な手を生成
	EXPAND(ban, node);

	for (u64_t i = 0; i < (*node->get_children()).size(); ++i) {
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
			}
			delete te;
			delete iti;
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
		}
		delete iti;
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
	PLAYER_EXPAND(ban, node);

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
			}
			//delete iti;
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
		}
		//delete iti;
	}

	return te;
}


Node *ai_turn(Node *root) {

	Node *node = max(root, -100000, 100000, 4);

	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			if (node->get_banmen()->get_type(x, y) != root->get_banmen()->get_type(x, y)) {
				/*
				*rootとnodeで盤面が異なる場合(AIが駒をとった可能性がある)
				*/
				if (root->get_banmen()->get_type(x, y) != EMPTY && node->get_banmen()->get_type(x, y) != EMPTY) {
					/*
					*EMPTYじゃない。つまり、駒をとった->プッシュします
					*/
					//ai_push_koma(ai_negaeri(root->get_banmen()->get_type(x, y)));
				}
			}
			//set_and_redraw(Point(std::abs(9 - x), y + 1), node->get_banmen()->get_type(x, y));
		}
	}
	
	
	return node;
}
