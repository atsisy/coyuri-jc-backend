#include "types.hpp"
#include "values.hpp"
#include <iostream>

BANMEN::BANMEN() {
	banmen = new KOMA_TYPE *[9];

	for (int i = 0; i < 9; i++) {
		banmen[i] = new KOMA_TYPE[9];
	}
}


BANMEN::~BANMEN() {
	for (int i = 0; i < 9; i++)
		delete[] banmen[i];

	delete[] banmen;
}

KOMA_TYPE BANMEN::get_type(int x, int y) {
	return banmen[x][y];
}

void BANMEN::set_type(int x, int y, KOMA_TYPE type) {
      banmen[x][y] = type;
}


void BANMEN::copy_banmen(BANMEN *original) {
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			banmen[x][y] = original->get_type(x, y);
		}
	}
}


Point BANMEN::find_koma(KOMA_TYPE type) {
	for (int x = 0; x < 9; x++)
		for (int y = 0; y < 9; y++)
			if (banmen[x][y] == type) return Point(x, y);

	/*
	*見つからないときは(-1, -1)を返す
	*/
	return Point(-1, -1);
}

Node::~Node() {
	delete banmen;
	delete ai_mochigoma;
	delete pl_mochigoma;
}

Node::Node(BANMEN *ban, Node *pare) {
	u8_t size, i;
	banmen = ban;
	parent = pare;

	ai_mochigoma = new MochiGoma;
	pl_mochigoma = new MochiGoma;

	size = pare->ai_mochigoma->size();
	for (i = 0; i < size; ++i) {
		ai_mochigoma->push_back(pare->ai_mochigoma->at(i));
	}
	
	size = pare->pl_mochigoma->size();
	for (i = 0; i < size; ++i) {
		pl_mochigoma->push_back(pare->pl_mochigoma->at(i));
	}

	evalue = 0;
}

Node::Node(BANMEN *ban, Node *pare, MochiGoma *ai_mochi, MochiGoma *pl_mochi) {
	banmen = ban;
	parent = pare;

	ai_mochigoma = ai_mochi;
	pl_mochigoma = pl_mochi;

	evalue = 0;
}


Node::Node(BANMEN *ban) {
	banmen = ban;
	parent = NULL;

	ai_mochigoma = new MochiGoma;
	pl_mochigoma = new MochiGoma;

	evalue = 0;
}

BANMEN *Node::get_banmen() {
	return banmen;
}

std::vector<Node *> *Node::get_children() {
	return &children;
}

int Node::get_evalue() {
	return evalue;
}

void Node::set_evalue(int value) {
	evalue = value;
}

void destroy_tree(Node *root) {
	for (Node *node : *root->get_children()) {
		if (node == NULL) continue;
		if (node->get_children()->size() > 0) {
			delete node;
		}
		else {
			destroy_tree(node);
			delete node;
		}
	}

}

bool win(KOMA_TYPE main_ban[9][9]) {
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			if (main_ban[x][y] == EN_OU) {
				return false;
			}
		}
	}
	return true;
}

bool lose(KOMA_TYPE main_ban[9][9]) {
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			if (main_ban[x][y] == OU) {
				return false;
			}
		}
	}
	return true;
}

KOMA_TYPE **BANMEN::get_banmen() {
	return this->banmen;
}
