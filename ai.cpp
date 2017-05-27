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
		//iti = max((*node->get_children()).at(i), alpha, beta, limit-1);
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


void ai_turn(Node *root) {

	int counters1[30] = { 0 };
	int counters2[30] = { 0 };

	Node *node = max(root, -100000, 100000, 4);
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			printf("%3d", node->get_banmen()->get_type(x, y));
			if (node->get_banmen()->get_type(x, y) != root->get_banmen()->get_type(x, y)) {
				/*
				*rootとnodeで盤面が異なる場合(AIが駒をとった可能性がある)
				*/
				if (root->get_banmen()->get_type(x, y) != EMPTY && node->get_banmen()->get_type(x, y) != EMPTY) {
					/*
					*EMPTYじゃない。つまり、駒をとった->プッシュします
					*/
					ai_push_koma(ai_negaeri(root->get_banmen()->get_type(x, y)));

				}
			}
			//set_and_redraw(Point(std::abs(9 - x), y + 1), node->get_banmen()->get_type(x, y));
		}
		std::cout << std::endl;
	}
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			counters1[root->get_banmen()->get_type(x, y)]++;
			counters2[node->get_banmen()->get_type(x, y)]++;
		}
	}

	/*
	*駒を打っていたかの判定
	*/
	for (int i = 1; i < 30; i++) {
		if (counters1[i] < counters2[i]) {
			for (int y = 0; y < 6; y++) {
				for (int x = 0; x < 6; x++) {
					if (ai_tegomas[y][x]->get_type() == i) {
						ai_tegomas[y][x]->set_type(EMPTY);
						//ai_tegomas[y][x]->image(images[EMPTY]);
						//ai_tegomas[y][x]->redraw();
					}
				}
			}
		}
	}
	std::cout << "eval:" << node->get_evalue() << std::endl;

	if (node->get_evalue() > 1088) {
		//今の盤面は良い
		//coyuri->image(coyuri_images[SMILE]);
		//coyuri->redraw();
	}
	else {
		//coyuri->image(coyuri_images[UMM]);
		//coyuri->redraw();
	}
}

void AI_START(KOMA_TYPE **main_ban) {
	/*
	*AIのターン
	*/
	if (!ai_finish_flag) {
		return;
	}

	ban = main_ban;

	BANMEN *banmen = new BANMEN;
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			banmen->set_type(x, y, main_ban[x][y]);
		}
	}
	Node *root = new Node(banmen, NULL);
	ai_turn(root);
	ai_finish_flag = false;
	player_finish_flag = false;
}
