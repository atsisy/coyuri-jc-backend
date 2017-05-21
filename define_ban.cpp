#include "ban.hpp"
#include "values.hpp"

Ban::Ban() {
	for (int y = 1; y <= 9; y++) {
		for (int x = 1; x <= 9; x++) {
			/*
			*裏で動く盤面変数はすべてEMPTYで初期化
			*/
			backend_ban[x - 1][y - 1] = EMPTY;
			frontend_ban[x - 1][y - 1] = new Masu(x*IMAGE_SIDE, y*IMAGE_SIDE, IMAGE_SIDE, IMAGE_SIDE);
			select_ban[x - 1][y - 1] = new Masu(x*IMAGE_SIDE, y*IMAGE_SIDE, IMAGE_SIDE, IMAGE_SIDE);

			frontend_ban[x - 1][y - 1]->image(nullptr);
			select_ban[x - 1][y - 1]->image(nullptr);
		}
	}
}
