#include "prot.hpp"
#include "values.hpp"
#include "types.hpp"

KOMA_TYPE not_naru() {
	return EMPTY;
}

KOMA_TYPE hu_naru() {
	return TOKIN;
}

KOMA_TYPE kyousha_naru() {
	return NARIKYOU;
}

KOMA_TYPE keima_naru() {
	return NARIKEI;
}

KOMA_TYPE gin_naru() {
	return NARIGIN;
}

KOMA_TYPE kin_naru() {
	return KIN;
}

KOMA_TYPE hisha_naru() {
	return RYU;
}

KOMA_TYPE kaku_naru() {
	return UMA;
}

KOMA_TYPE en_hu_naru() {
	return EN_TOKIN;
}

KOMA_TYPE en_kyousha_naru() {
	return EN_NARIKYOU;
}

KOMA_TYPE en_keima_naru() {
	return EN_NARIKEI;
}

KOMA_TYPE en_gin_naru() {
	return EN_NARIGIN;
}

KOMA_TYPE en_kin_naru() {
	return EN_KIN;
}

KOMA_TYPE en_hisha_naru() {
	return EN_RYU;
}

KOMA_TYPE en_kaku_naru() {
	return EN_UMA;
}


KOMA_TYPE(*naru_ftable[])() = {
	not_naru,
	not_naru,
	hu_naru,
	kyousha_naru,
	keima_naru,
	gin_naru,
	kin_naru,
	hisha_naru,
	kaku_naru,
	not_naru,
	not_naru,
	not_naru,
	not_naru,
	not_naru,
	not_naru,
	not_naru,
	en_hu_naru,
	en_kyousha_naru,
	en_keima_naru,
	en_gin_naru,
	en_kin_naru,
	en_hisha_naru,
	en_kaku_naru,
};
