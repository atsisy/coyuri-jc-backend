#include "types.hpp"
#include "values.hpp"
#include "prot.hpp"

std::vector<Point> where_can_move(Point point, KOMA_TYPE type) {
	std::vector<Point> points;
	switch (type) {
	case HU:
		/*
		*もしも敵の一番置くまで進んでいたら何も挿入せずに返す
		*/
		if (point.get_y() == 1) break;
		/*
		*座標を挿入
		*/
		points.push_back(Point(point.get_x(), point.get_y() - 1));
		break;
	default:
		break;
	}
	return points;
}

bool empty(KOMA_TYPE **main_ban, int x, int y) {
	return main_ban[9 - x][y - 1] == EMPTY;
}

bool enemy(KOMA_TYPE **main_ban, int x, int y) {
	return main_ban[9 - x][y - 1] >= EN_HU && main_ban[9 - x][y - 1] <= EN_OU;
}

bool my_koma(KOMA_TYPE **main_ban, int x, int y) {
	return main_ban[9 - x][y - 1] >= HU && main_ban[9 - x][y - 1] <= OU;
}

bool can_target(KOMA_TYPE **ban, int x, int y) {
	return (empty(ban, x, y) || enemy(ban, x, y)) && (x > 0 && x <= 9) && (y > 0 && y <= 9);
}

bool jands_one_wcm(KOMA_TYPE **ban, int x, int y, std::vector<Point> *points) {
	if (enemy(ban, x, y) && (x > 0 && x <= 9) && (y > 0 && y <= 9)) {
		points->push_back(Point(x, y));
		return false;
	}
	if (can_target(ban, x, y)) {
		points->push_back(Point(x, y));
		return true;
	}
	return false;
}

bool ai_can_target(KOMA_TYPE **ban, int x, int y) {
	return (empty(ban, x, y) || my_koma(ban, x, y)) && (x > 0 && x <= 9) && (y > 0 && y <= 9);
}


bool ai_jands_one_wcm(KOMA_TYPE **ban, int x, int y, std::vector<Point> *points) {
	if (my_koma(ban, x, y) && (x > 0 && x <= 9) && (y > 0 && y <= 9)) {
		points->push_back(Point(x, y));
		return false;
	}
	if (ai_can_target(ban, x, y)) {
		points->push_back(Point(x, y));
		return true;
	}
	return false;
}

/*
*駒を変換する関数
*/
KOMA_TYPE naru(KOMA_TYPE type) {
	switch (type) {
	case HU:
		return TOKIN;
	case KYOUSHA:
		return NARIKYOU;
	case KEIMA:
		return NARIKEI;
	case GIN:
		return NARIGIN;
	case HISHA:
		return RYU;
	case KAKU:
		return UMA;
	case EN_HU:
		return EN_TOKIN;
	case EN_KYOUSHA:
		return EN_NARIKYOU;
	case EN_KEIMA:
		return EN_NARIKEI;
	case EN_GIN:
		return EN_NARIGIN;
	case EN_HISHA:
		return EN_RYU;
	case EN_KAKU:
		return EN_UMA;
	default:
		return type;
	}
}

/*
*敵を味方に変換する関数
*/
KOMA_TYPE negaeri(KOMA_TYPE type) {
	switch (type) {
	case EN_HU:
		return HU;
	case EN_KYOUSHA:
		return KYOUSHA;
	case EN_KEIMA:
		return KEIMA;
	case EN_GIN:
		return GIN;
	case EN_KIN:
		return KIN;
	case EN_HISHA:
		return HISHA;
	case EN_KAKU:
		return KAKU;
	case EN_TOKIN:
		return HU;
	case EN_NARIKYOU:
		return KYOUSHA;
	case EN_NARIKEI:
		return KEIMA;
	case EN_NARIGIN:
		return GIN;
	case EN_RYU:
		return HISHA;
	case EN_UMA:
		return KAKU;
	default:
		return type;
	}
}

/*
*プレイヤーに変換する関数
*/
KOMA_TYPE ai_negaeri(KOMA_TYPE type) {
	switch (type) {
	case HU:
		return EN_HU;
	case KYOUSHA:
		return EN_KYOUSHA;
	case KEIMA:
		return EN_KEIMA;
	case GIN:
		return EN_GIN;
	case KIN:
		return EN_KIN;
	case HISHA:
		return EN_HISHA;
	case KAKU:
		return EN_KAKU;
	case TOKIN:
		return EN_HU;
	case NARIKYOU:
		return EN_KYOUSHA;
	case NARIKEI:
		return EN_KEIMA;
	case NARIGIN:
		return EN_GIN;
	case RYU:
		return EN_HISHA;
	case UMA:
		return EN_KAKU;
	default:
		return type;
	}
}
