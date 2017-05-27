#include <iostream>
#include "types.hpp"
#include "prot.hpp"

Masu *visual_ban[9][9];
Point TARGET_KOMA;
Tegoma *player_tegomas[6][6];
Tegoma *ai_tegomas[6][6];
KOMA_TYPE UTSU;
Point UTSU_KOMA;

std::vector<Point> (*wcm_ftable[])(KOMA_TYPE **ban, Point point) = {
	null_wcm,
	null_wcm,
	pl_hu_wcm,
	pl_kyousha_wcm,
	pl_keima_wcm,
	pl_gin_wcm,
	pl_kin_wcm,
	pl_hisha_wcm,
	pl_kaku_wcm,
	pl_kin_wcm,
	pl_kin_wcm,
	pl_kin_wcm,
	pl_kin_wcm,
	pl_ryu_wcm,
	pl_uma_wcm,
	pl_ou_wcm,
	ai_hu_wcm,
	ai_kyousha_wcm,
	ai_keima_wcm,
	ai_gin_wcm,
	ai_kin_wcm,
	ai_hisha_wcm,
	ai_kaku_wcm,
	ai_kin_wcm,
	ai_kin_wcm,
	ai_kin_wcm,
	ai_kin_wcm,
	ai_ryu_wcm,
	ai_uma_wcm,
	ai_ou_wcm,
	tegoma_wcm
};

void AI_START(KOMA_TYPE **main_ban);

int main(int argc, char **argv) {

	KOMA_TYPE main_ban[9][9];

	AI_START((KOMA_TYPE **)main_ban);
}
