#include "types.hpp"
#include "values.hpp"

/*
*駒を版にセットし再描画する関数
*/
void set_and_redraw(Point p, KOMA_TYPE type) {
	visual_ban[9 - p.get_x()][p.get_y() - 1]->image(images[type]);
	visual_ban[9 - p.get_x()][p.get_y() - 1]->redraw();
	main_ban[9 - p.get_x()][p.get_y() - 1] = type;
}

void target_masu(Point p) {
	target_ban[9 - p.get_x()][p.get_y() - 1]->image(images[TARGET]);
	target_ban[9 - p.get_x()][p.get_y() - 1]->redraw();
}

void target_clear() {
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			if (target_ban[x][y]->image() == images[TARGET]) {
				target_ban[x][y]->image(images[main_ban[x][y]]);
				target_ban[x][y]->redraw();
			}
		}
	}
	UTSU = EMPTY;
}
