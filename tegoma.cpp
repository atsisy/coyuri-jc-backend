#include "types.hpp"
#include "prot.hpp"
#include "values.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
/*
std::vector<KOMA_TYPE> AI_TEGOMA;
std::vector<KOMA_TYPE> PLAYER_TEGOMA;

Tegoma::Tegoma(int x, int y, int width, int height, int in_x, int in_y, KOMA_TYPE arg_type) {
	X = in_x;
	Y = in_y;
	type = arg_type;
}


void player_push_koma(KOMA_TYPE type) {
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 6; x++) {
			if (!player_tegomas[x][y]->get_type()) {
				player_tegomas[x][y]->set_type(type);
				return;
			}
		}
	}
}

void ai_push_koma(KOMA_TYPE type) {
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 6; x++) {
			if (ai_tegomas[x][y]->get_type() == EMPTY) {
				ai_tegomas[x][y]->set_type(type);
				return;
			}
		}
	}
}


void show_tegoma() {
	std::cout << "Player:";

	for (KOMA_TYPE koma : AI_TEGOMA) {
		std::cout << koma << " ";
	}
	std::cout << std::endl;
}

void Tegoma::set_type(KOMA_TYPE arg_type) {
	type = arg_type;
}

*/