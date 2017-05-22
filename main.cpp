#include <FL/fl_ask.H>
#include <FL/Fl_Button.H>
#include <iostream>
#include "types.hpp"
#include "prot.hpp"

Masu *visual_ban[9][9];
Fl_Box *target_ban[9][9];
KOMA_TYPE main_ban[9][9];
Fl_PNG_Image *images[30];
Fl_PNG_Image *coyuri_images[4];
Fl_PNG_Image *clear;
Point TARGET_KOMA;
Fl_Box *message;
Fl_Box *coyuri;
Tegoma *player_tegomas[6][6];
Tegoma *ai_tegomas[6][6];
KOMA_TYPE UTSU;
Point UTSU_KOMA;

std::vector<Point> (*wcm_ftable[])(Point point) = {
	null_wcm,
	null_wcm,
	hu_wcm,
	kyousha_wcm,
	keima_wcm,
	gin_wcm,
	kin_wcm,
	hisha_wcm,
	kaku_wcm,
	kin_wcm,
	kin_wcm,
	kin_wcm,
	kin_wcm,
	ryu_wcm,
	uma_wcm,
	ou_wcm,
	en_hu_wcm,
	en_kyousha_wcm,
	en_keima_wcm,
	en_gin_wcm,
	en_kin_wcm,
	en_hisha_wcm,
	en_kaku_wcm,
	en_kin_wcm,
	en_kin_wcm,
	en_kin_wcm,
	en_kin_wcm,
	en_ryu_wcm,
	en_uma_wcm,
	en_ou_wcm,
	tegoma_wcm
};

void toryo(Fl_Widget* widget);

int main(int argc, char **argv) {

	fl_register_images();
	Fl_Window win(1200, 1000, "Coyuri");

	UTSU = EMPTY;

	banmen_init(visual_ban, target_ban, main_ban);
	tegoma_init(player_tegomas, ai_tegomas);

	clear = new Fl_PNG_Image("/home/takai/Pictures/coyuri/clear.png");
	init();
	Fl_Button *next = new Fl_Button(550, 710, 150, 100, /*"こゆりちゃんの手番へ"*/"next");
	next->callback(AI_START);
	Fl_Button *toryo_button = new Fl_Button(550, 820, 150, 100, "fin");
	toryo_button->callback(toryo);
	//next->callback(AI_START);

	message = new Fl_Box(280, 800, 300, 50, "手加減してくれるとうれしいな。");

	coyuri = new Fl_Box(40, 700, 300, 300);
	coyuri->image(coyuri_images[DEFAULT]);

	//win.end();
	win.show(argc, argv);

	return Fl::run();
}

void toryo(Fl_Widget* widget) {
	if (fl_ask("投了しますか？")) {
		update_score(true);
		exit(1);
	}
}
