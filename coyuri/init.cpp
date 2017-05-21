#include "values.hpp"
#include "types.hpp"
#include "prot.hpp"

void images_path_init() {
	/*
	*駒が置かれていない
	*/
	images[EMPTY] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\ban.png");
	images[TARGET] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\target.png");

	/*
	*味方
	*/
	images[HU] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\hu.png");
	images[KYOUSHA] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\kyousha.png");
	images[KEIMA] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\keima.png");
	images[GIN] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\gin.png");
	images[KIN] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\kin.png");
	images[HISHA] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\hisha.png");
	images[KAKU] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\kaku.png");
	images[TOKIN] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\tokin.png");
	images[NARIKYOU] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\narikyou.png");
	images[NARIKEI] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\narikei.png");
	images[NARIGIN] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\narigin.png");
	images[RYU] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\ryu.png");
	images[UMA] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\uma.png");
	images[OU] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\ou.png");

	/*
	*敵側
	*/
	images[EN_HU] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\en_hu.png");
	images[EN_KYOUSHA] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\en_kyousha.png");
	images[EN_KEIMA] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\en_keima.png");
	images[EN_GIN] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\en_gin.png");
	images[EN_KIN] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\en_kin.png");
	images[EN_HISHA] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\en_hisha.png");
	images[EN_KAKU] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\en_kaku.png");
	images[EN_TOKIN] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\en_tokin.png");
	images[EN_NARIKYOU] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\en_narikyou.png");
	images[EN_NARIKEI] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\en_narikei.png");
	images[EN_NARIGIN] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\en_narigin.png");
	images[EN_RYU] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\en_ryu.png");
	images[EN_UMA] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\en_uma.png");
	images[EN_OU] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\en_ou.png");

	/*coyuri1の画像
	coyuri_images[DEFAULT] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\default.png");
	coyuri_images[SMILE]   = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\sml.png");
	coyuri_images[UMM]     = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\umm.png");
	*/
	coyuri_images[DEFAULT] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\c2_nor.png");
	coyuri_images[SMILE] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\c2_sm.png");
	coyuri_images[UMM] = new Fl_PNG_Image("C:\\Users\\Akihiro\\Pictures\\image\\c2_dmd.png");
}

/*
*駒ｗｐ初期位置に配置する関数
*/
void put_koma_init() {
	for (int y = 1; y <= 9; y++) {
		for (int x = 1; x <= 9; x++) {
			set_and_redraw(Point(x, y), EMPTY);
		}
	}
	/*
	*味方
	*/
	set_and_redraw(Point(9, 9), KYOUSHA);
	set_and_redraw(Point(8, 9), KEIMA);
	set_and_redraw(Point(7, 9), GIN);
	set_and_redraw(Point(6, 9), KIN);
	set_and_redraw(Point(5, 9), OU);
	set_and_redraw(Point(1, 9), KYOUSHA);
	set_and_redraw(Point(2, 9), KEIMA);
	set_and_redraw(Point(3, 9), GIN);
	set_and_redraw(Point(4, 9), KIN);
	set_and_redraw(Point(2, 8), HISHA);
	set_and_redraw(Point(8, 8), KAKU);
	for (int i = 1; i <= 9; i++)
		set_and_redraw(Point(i, 7), HU);

	/*
	*敵側
	*/
	set_and_redraw(Point(9, 1), EN_KYOUSHA);
	set_and_redraw(Point(8, 1), EN_KEIMA);
	set_and_redraw(Point(7, 1), EN_GIN);
	set_and_redraw(Point(6, 1), EN_KIN);
	set_and_redraw(Point(5, 1), EN_OU);
	set_and_redraw(Point(1, 1), EN_KYOUSHA);
	set_and_redraw(Point(2, 1), EN_KEIMA);
	set_and_redraw(Point(3, 1), EN_GIN);
	set_and_redraw(Point(4, 1), EN_KIN);
	set_and_redraw(Point(8, 2), EN_HISHA);
	set_and_redraw(Point(2, 2), EN_KAKU);
	for (int i = 1; i <= 9; i++)
		set_and_redraw(Point(i, 3), EN_HU);

}

/*
*初期化を行う関数
*/
void init() {
	images_path_init();
	put_koma_init();
	Fl_Box *gyou = new Fl_Box(100, 20, 560, 65, "9              8               7                6                 5                4               3                2              1");
	Fl_Box *suji = new Fl_Box(660, 78, 110, 610, "i\n\n\n\n\n二\n\n\n\n\n三\n\n\n\n\n四\n\n\n\n\n五\n\n\n\n\n六\n\n\n\n\n七\n\n\n\n\n八\n\n\n\n\n九");

	player_finish_flag = false;
	ai_finish_flag = false;
}

void banmen_init(Masu *visual_ban[9][9], Fl_Box *target_ban[9][9], KOMA_TYPE main_ban[9][9]) {
	for (int y = 1; y <= 9; y++) {
		for (int x = 1; x <= 9; x++) {
			/*
			*裏で動く盤面変数はすべてEMPTYで初期化
			*/
			main_ban[x - 1][y - 1] = EMPTY;
			visual_ban[x - 1][y - 1] = new Masu(x*IMAGE_SIDE, y*IMAGE_SIDE, IMAGE_SIDE, IMAGE_SIDE);
			target_ban[x - 1][y - 1] = new Masu(x*IMAGE_SIDE, y*IMAGE_SIDE, IMAGE_SIDE, IMAGE_SIDE);

			visual_ban[x - 1][y - 1]->image(nullptr);
			target_ban[x - 1][y - 1]->image(nullptr);
		}
	}
}

void tegoma_init(Tegoma *player_tegomas[6][6], Tegoma *ai_tegomas[6][6]) {
	for (int y = 0; y < 6; ++y) {
		for (int x = 0; x < 6; ++x) {

			player_tegomas[x][y] = new Tegoma(70 * x + 749, 70 * y + 500, 70, 70, x, y, EMPTY);
			player_tegomas[x][y]->image(images[EMPTY]);

			ai_tegomas[x][y] = new Tegoma(70 * x + 749, 70 * y + 49, 70, 70, x, y, EMPTY);
			ai_tegomas[x][y]->image(images[EMPTY]);
		}
	}
}