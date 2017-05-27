#include "types.hpp"
#include "prot.hpp"
#include "values.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

std::vector<KOMA_TYPE> AI_TEGOMA;
std::vector<KOMA_TYPE> PLAYER_TEGOMA;

Tegoma::Tegoma(int x, int y, int width, int height, int in_x, int in_y, KOMA_TYPE arg_type) {
	X = in_x;
	Y = in_y;
	type = arg_type;
}

int Tegoma::handle(int event) {
	//if (event == FL_RELEASE) {
	//	//target_clear();
	//	if (type == EMPTY) {
	//		return 1;
	//	}
	//	if (type == HU) {
	//		for (Point point : nihu_wcm()) {
	//			//target_masu(point);
	//		}
	//	}
	//	else {
	//		for (Point point : wcm_ftable[TEGOMA](Point(0, 0))) {
	//			//target_masu(point);
	//		}
	//	}
	//	UTSU = type;
	//	UTSU_KOMA.set_x(X);
	//	UTSU_KOMA.set_y(Y);
	//}

	return 1;
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

/*
void PLAYER_UTSU(KOMA_TYPE type, Point p) {

	set_and_redraw(p, type);

	player_tegomas[UTSU_KOMA.get_x()][UTSU_KOMA.get_y()]->set_type(EMPTY);
	player_tegomas[UTSU_KOMA.get_x()][UTSU_KOMA.get_y()]->image(images[EMPTY]);
	player_tegomas[UTSU_KOMA.get_x()][UTSU_KOMA.get_y()]->redraw();

}
*/

