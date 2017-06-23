#include "prot.hpp"
#include "values.hpp"
#include "types.hpp"
#include <iostream>
#include <stdio.h>
#include <cmath>

/*
*wcm関数内では通常の将棋の盤面を操作する感じで行う
*/

//何もしないwcm関数
std::vector<Point> null_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;
	return points;
}

//歩のwcm関数
std::vector<Point> pl_hu_wcm(KOMA_TYPE **ban, Point point) {
	std::vector<Point> points;

	/*
	*一つ前方を確認
	*/
	pl_targetable(ban, point.x, point.y - 1, &points);

	return points;
}

std::vector<Point> pl_kyousha_wcm(KOMA_TYPE **ban, Point point) {
	std::vector<Point> points;

	u8_t x = point.x, y = point.y;

	do {
		--y;
	} while (pl_targetable(ban, x, y, &points));

	return points;
}

//桂馬のwcm関数
std::vector<Point> pl_keima_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x, y = p.y;

	/*
	*２つ前に進めない位置にいる場合移動できない
	*/
	if (x <= 2) {
		return points;
	}

	pl_targetable(ban, x + 1, y - 2, &points);
	pl_targetable(ban, x - 1, y - 2, &points);

	return points;
}

//銀のwcm関数
std::vector<Point> pl_gin_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x, y = p.y;

	/*
	*前方方向の移動可能判定
	*/
	pl_targetable(ban, x - 1, y - 1, &points);
	pl_targetable(ban, x, y - 1, &points);
	pl_targetable(ban, x + 1, y - 1, &points);

	/*
	*後方方向の移動可能判定
	*/
	pl_targetable(ban, x - 1, y + 1, &points);
	pl_targetable(ban, x + 1, y + 1, &points);

	return points;
}

//銀のwcm関数
std::vector<Point> pl_kin_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x, y = p.y;

	/*
	*前方方向の移動可能判定
	*/
	pl_targetable(ban, p.x - 1, p.y - 1, &points);
	pl_targetable(ban, p.x, p.y - 1, &points);
	pl_targetable(ban, p.x + 1, p.y - 1, &points);

	/*
	*横方向の移動可能判定
	*/
	pl_targetable(ban, x - 1, p.y, &points);
	pl_targetable(ban, x + 1, p.y, &points);

	/*
	*後方方向の移動可能判定
	*/
	pl_targetable(ban, x, p.y + 1, &points);

	return points;
}

//飛車のwcm関数
std::vector<Point> pl_hisha_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;
	u8_t x = p.x - 1, y;

	/*
	*左方向の移動可能判定
	*/
	while (pl_targetable(ban, x, p.y, &points)) {
		x--;
	}

	/*
	*左方向の移動可能判定
	*/
	x = p.x + 1;
	while (pl_targetable(ban, x, p.y, &points)) {
		x++;
	}

	/*
	*下方向の移動可能判定
	*/
	y = p.y + 1;
	while (pl_targetable(ban, p.x, y, &points)) {
		y++;
	}

	/*
	*上方向の移動可能判定
	*/
	y = p.y - 1;
	while (pl_targetable(ban, p.x, y, &points)) {
		y--;
	}

	return points;
}

//角のwcm関数
std::vector<Point> pl_kaku_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x - 1, y = p.y - 1;
	/*
	*右上方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x--;
		y--;
	}

	x = p.x + 1;
	y = p.y - 1;
	/*
	*左上方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x++;
		y--;
	}

	x = p.x - 1;
	y = p.y + 1;
	/*
	*右下方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x--;
		y++;
	}

	x = p.x + 1;
	y = p.y + 1;
	/*
	*右下方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x++;
		y++;
	}

	return points;
}

//王将のwcm関数
std::vector<Point> pl_ou_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x, y = p.y;

	//前方方向の移動可能判定
	pl_targetable(ban, x, p.y - 1, &points);
	pl_targetable(ban, x - 1, p.y - 1, &points);
	pl_targetable(ban, x + 1, p.y - 1, &points);

	//横方向の移動可能判定
	pl_targetable(ban, x + 1, p.y, &points);
	pl_targetable(ban, x - 1, p.y, &points);

	//後方方向の移動可能判定
	pl_targetable(ban, x, p.y + 1, &points);
	pl_targetable(ban, x - 1, p.y + 1, &points);
	pl_targetable(ban, x + 1, p.y + 1, &points);

	return points;
}

//龍のwcm関数
std::vector<Point> pl_ryu_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;
	u8_t x = p.x - 1, y;

	/*
	*左方向の移動可能判定
	*/
	while (pl_targetable(ban, x, p.y, &points)) {
		x--;
	}

	/*
	*左方向の移動可能判定
	*/
	x = p.x + 1;
	while (pl_targetable(ban, x, p.y, &points)) {
		x++;
	}

	/*
	*下方向の移動可能判定
	*/
	y = p.y + 1;
	while (pl_targetable(ban, p.x, y, &points)) {
		y++;
	}

	/*
	*上方向の移動可能判定
	*/
	y = p.y - 1;
	while (pl_targetable(ban, p.x, y, &points)) {
		y--;
	}

	x = p.x;
	y = p.y;
	//斜め上方向の移動可能判定
	pl_targetable(ban, x - 1, p.y - 1, &points);
	pl_targetable(ban, x + 1, p.y - 1, &points);

	//斜め下方向の移動可能判定
	pl_targetable(ban, x - 1, p.y + 1, &points);
	pl_targetable(ban, x + 1, p.y + 1, &points);

	return points;
}

//馬のwcm関数
std::vector<Point> pl_uma_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x - 1, y = p.y - 1;
	/*
	*右上方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x--;
		y--;
	}

	x = p.x + 1;
	y = p.y - 1;
	/*
	*左上方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x++;
		y--;
	}

	x = p.x - 1;
	y = p.y + 1;
	/*
	*右下方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x--;
		y++;
	}

	x = p.x + 1;
	y = p.y + 1;
	/*
	*右下方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x++;
		y++;
	}

	x = p.x;
	y = p.y;
	//横方向の移動可能判定
	pl_targetable(ban, x + 1, y, &points);
	pl_targetable(ban, x - 1, y, &points);

	//前方の移動可能判定
	pl_targetable(ban, x, y - 1, &points);

	//後方方向の移動可能判定
	pl_targetable(ban, x, y + 1, &points);

	return points;
}


//AIの歩のwcm関数
std::vector<Point> ai_hu_wcm(KOMA_TYPE **ban, Point point) {
	std::vector<Point> points;

	/*
	*一つ前方を確認
	*/
	ai_targetable(ban, point.x, point.y + 1, &points);
	

	return points;
}

//敵の香車のwcm関数
std::vector<Point> ai_kyousha_wcm(KOMA_TYPE **ban, Point point) {
	std::vector<Point> points;

	u8_t y = point.y + 1;
	while (ai_targetable(ban, point.x, y, &points)) {
		y++;
	}
	return points;
}

//敵の桂馬のwcm関数
std::vector<Point> ai_keima_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	ai_targetable(ban, p.x + 1, p.y + 2, &points);
	ai_targetable(ban, p.x - 1, p.y + 2, &points);

	return points;
}

//敵の銀のwcm関数
std::vector<Point> ai_gin_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	/*
	*前方方向の移動可能判定
	*/
	ai_targetable(ban, p.x - 1, p.y + 1, &points);
	ai_targetable(ban, p.x, p.y + 1, &points);
	ai_targetable(ban, p.x + 1, p.y + 1, &points);

	/*
	*後方方向の移動可能判定
	*/
	ai_targetable(ban, p.x - 1, p.y - 1, &points);
	ai_targetable(ban, p.x + 1, p.y - 1, &points);

	return points;
}

//敵の金のwcm関数
std::vector<Point> ai_kin_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	/*
	*前方方向の移動可能判定
	*/
	ai_targetable(ban, p.x - 1, p.y + 1, &points);
	ai_targetable(ban, p.x, p.y + 1, &points);
	ai_targetable(ban, p.x + 1, p.y + 1, &points);

	/*
	*横方向の移動可能判定
	*/
	ai_targetable(ban, p.x - 1, p.y, &points);
	ai_targetable(ban, p.x + 1, p.y, &points);

	/*
	*後方方向の移動可能判定
	*/
	ai_targetable(ban, p.x, p.y - 1, &points);

	return points;
}

//敵の飛車のwcm関数
std::vector<Point> ai_hisha_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;
	u8_t x = p.x, y = p.y;

	/*
	*左方向の移動可能判定
	*/
	do {
		--x;
	} while (ai_targetable(ban, x, y, &points));

	/*
	*左方向の移動可能判定
	*/
	x = p.x;
	do {
		++x;
	} while (ai_targetable(ban, x, y, &points));

	/*
	*下方向の移動可能判定
	*/
	y = p.y;
	x = p.x;
	do {
		--y;
	} while (ai_targetable(ban, x, y, &points));

	/*
	*上方向の移動可能判定
	*/
	y = p.y;
	do {
		++y;
	} while (ai_targetable(ban, p.x, y, &points));

	return points;
}

//敵の角のwcm関数
std::vector<Point> ai_kaku_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x - 1, y = p.y - 1;
	/*
	*右上方向の移動可能判定
	*/
	while (ai_targetable(ban, x, y, &points)) {
		x--;
		y--;
	}

	x = p.x + 1;
	y = p.y - 1;
	/*
	*左上方向の移動可能判定
	*/
	while (ai_targetable(ban, x, y, &points)) {
		x++;
		y--;
	}

	x = p.x - 1;
	y = p.y + 1;
	/*
	*右下方向の移動可能判定
	*/
	while (ai_targetable(ban, x, y, &points)) {
		x--;
		y++;
	}

	x = p.x + 1;
	y = p.y + 1;
	/*
	*右下方向の移動可能判定
	*/
	while (ai_targetable(ban, x, y, &points)) {
		x++;
		y++;
	}

	return points;
}

//敵の王将のwcm関数
std::vector<Point> ai_ou_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	//前方方向の移動可能判定
	ai_targetable(ban, p.x, p.y - 1, &points);
	ai_targetable(ban, p.x - 1, p.y - 1, &points);
	ai_targetable(ban, p.x + 1, p.y - 1, &points);

	//横方向の移動可能判定
	ai_targetable(ban, p.x + 1, p.y, &points);
	ai_targetable(ban, p.x - 1, p.y, &points);

	//後方方向の移動可能判定
	ai_targetable(ban, p.x, p.y + 1, &points);
	ai_targetable(ban, p.x - 1, p.y + 1, &points);
	ai_targetable(ban, p.x + 1, p.y + 1, &points);

	return points;
}


//龍のwcm関数
std::vector<Point> ai_ryu_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;
	u8_t x = p.x - 1, y;

	/*
	*左方向の移動可能判定
	*/
	while (ai_targetable(ban, x, p.y, &points)) {
		x--;
	}

	/*
	*左方向の移動可能判定
	*/
	x = p.x + 1;
	while (ai_targetable(ban, x, p.y, &points)) {
		x++;
	}

	/*
	*下方向の移動可能判定
	*/
	y = p.y + 1;
	while (ai_targetable(ban, p.x, y, &points)) {
		y++;
	}

	/*
	*上方向の移動可能判定
	*/
	y = p.y - 1;
	while (ai_targetable(ban, p.x, y, &points)) {
		y--;
	}

	//斜め上方向の移動可能判定
	ai_targetable(ban, p.x - 1, p.y - 1, &points);
	ai_targetable(ban, p.x + 1, p.y - 1, &points);

	//斜め下方向の移動可能判定
	ai_targetable(ban, p.x - 1, p.y + 1, &points);
	ai_targetable(ban, p.x + 1, p.y + 1, &points);

	return points;
}

//馬のwcm関数
std::vector<Point> ai_uma_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x - 1, y = p.y - 1;
	/*
	*右上方向の移動可能判定
	*/
	while (ai_targetable(ban, x, y, &points)) {
		x--;
		y--;
	}

	x = p.x + 1;
	y = p.y - 1;
	/*
	*左上方向の移動可能判定
	*/
	while (ai_targetable(ban, x, y, &points)) {
		x++;
		y--;
	}

	x = p.x - 1;
	y = p.y + 1;
	/*
	*右下方向の移動可能判定
	*/
	while (ai_targetable(ban, x, y, &points)) {
		x--;
		y++;
	}

	x = p.x + 1;
	y = p.y + 1;
	/*
	*右下方向の移動可能判定
	*/
	while (ai_targetable(ban, x, y, &points)) {
		x++;
		y++;
	}

	//横方向の移動可能判定
	ai_targetable(ban, p.x + 1, p.y, &points);
	ai_targetable(ban, p.x - 1, p.y, &points);

	//前方の移動可能判定
	ai_targetable(ban, p.x, p.y - 1, &points);

	//後方方向の移動可能判定
	ai_targetable(ban, p.x, p.y + 1, &points);

	return points;

}

//手駒のwcm関数
std::vector<Point> tegoma_wcm(KOMA_TYPE **main_ban, Point p) {
	std::vector<Point> points;
	for (u8_t y = 0; y < 9; y++) {
		for (u8_t x = 0; x < 9; x++) {
			if (_IS_EMPTY(main_ban[x][y])) {
				points.push_back(point(x, y));
			}
		}
	}
	return points;
}

//打つときに、二歩にならないためのwcm関数
std::vector<Point> nihu_wcm(KOMA_TYPE **main_ban) {
	std::vector<Point> points;
	bool nihu = false;

	for (u8_t x = 0; x < 9; x++) {
		for (u8_t y = 0; y < 9; y++) {
			if (main_ban[x][y] == HU) {
				/*
				*歩があった
				*/
				nihu = true;
			}
		}
		if (!nihu) {
			/*
			*歩が見つからない場合、その一行を追加
			*/
			for (int y = 1; y < 9; y++) {
				if (_IS_EMPTY(main_ban[x][y]) && main_ban[x][y - 1] != EN_OU) {
					points.push_back(point(x, y));
				}
			}
		}
		nihu = false;
	}

	return points;
}

//打つときに、二歩にならないためのwcm関数(ai用)
std::vector<Point> ai_nihu_wcm(KOMA_TYPE **main_ban) {
	std::vector<Point> points;
	bool nihu = false;

	for (u8_t x = 0; x < 9; x++) {
		for (u8_t y = 0; y < 9; y++) {
			if (main_ban[x][y] == EN_HU) {
				/*
				*歩があった
				*/
				nihu = true;
			}
		}
		if (!nihu) {
			/*
			*歩が見つからない場合、その一行を追加
			*/
			for (u8_t y = 0; y < 8; y++) {
				if (_IS_EMPTY(main_ban[x][y]) && main_ban[x][y + 1] != OU) {
					points.push_back(point(x, y));
				}
			}
		}
		nihu = false;
	}

	return points;
}

u8_t ai_targetable(KOMA_TYPE **ban, u8_t x, u8_t y, std::vector<Point>  *points){

	//盤面外なのでだめ
	if(x < 0 || x > 8 || y < 0 || y > 8){
		return false;
	}

	//EMPTYなので、特に制限はない
	if(_IS_EMPTY(ban[x][y])){
		points->push_back(point(x, y));
		return true;
	}

	//プレイヤーの駒なので、取ることができる
	if(_IS_PLAYER_KOMA((u8_t)ban[x][y])){
		points->push_back(point(x, y));
		return false;
	}

	//自分の駒（AI）なので、移動することはできない
	if(_IS_AI_KOMA(ban[x][y])){
		return false;
	}

	return false;
}

u8_t pl_targetable(KOMA_TYPE **ban, u8_t x, u8_t y, std::vector<Point>  *points){
      //盤面外なのでだめ
	if(x < 0 || x > 8 || y < 0 || y > 8){
		return false;
	}

	//EMPTYなので、特に制限はない
	if(_IS_EMPTY(ban[x][y])){
		points->push_back(point(x, y));
		return true;
	}

	//AIの駒なので、取ることができる
	if(_IS_AI_KOMA(ban[x][y])){
		points->push_back(point(x, y));
		return false;
	}

	//相手（プレイヤー）なので、移動することはできない
	if(_IS_PLAYER_KOMA(ban[x][y])){
		return false;
	}

	return false;
}
