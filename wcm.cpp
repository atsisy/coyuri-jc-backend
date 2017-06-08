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
      pl_targetable(ban, point.get_x(), point.get_y() - 1, &points);

	return points;
}

std::vector<Point> pl_kyousha_wcm(KOMA_TYPE **ban, Point point) {
	std::vector<Point> points;
	
	u8_t x = point.get_x(), y = point.get_y();

	do{
		--y;
	}while(pl_targetable(ban, x, y, &points));
	
	return points;
}

//桂馬のwcm関数
std::vector<Point> pl_keima_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.get_x(), y = p.get_y();

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

	u8_t x = p.get_x(), y = p.get_y();

	/*
	*前方方向の移動可能判定
	*/
	pl_targetable(ban, x - 1, y - 1, &points);
	pl_targetable(ban, x,     y - 1, &points);
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

	u8_t x = p.get_x(), y = p.get_y();

	/*
	*前方方向の移動可能判定
	*/
	pl_targetable(ban, p.get_x() - 1, p.get_y() - 1, &points);
	pl_targetable(ban, p.get_x(), p.get_y() - 1, &points);
	pl_targetable(ban, p.get_x() + 1, p.get_y() - 1, &points);

	/*
	*横方向の移動可能判定
	*/
	pl_targetable(ban, x - 1, p.get_y(), &points);
	pl_targetable(ban, x + 1, p.get_y(), &points);

	/*
	*後方方向の移動可能判定
	*/
	pl_targetable(ban, x, p.get_y() + 1, &points);

	return points;
}

//飛車のwcm関数
std::vector<Point> pl_hisha_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;
	int x = p.get_x() - 1, y;

	/*
	*左方向の移動可能判定
	*/
	while (pl_targetable(ban, x, p.get_y(), &points)) {
		x--;
	}

	/*
	*左方向の移動可能判定
	*/
	x = p.get_x() + 1;
	while (pl_targetable(ban, x, p.get_y(), &points)) {
		x++;
	}

	/*
	*下方向の移動可能判定
	*/
	y = p.get_y() + 1;
	while (pl_targetable(ban, p.get_x(), y, &points)) {
		y++;
	}

	/*
	*上方向の移動可能判定
	*/
	y = p.get_y() - 1;
	while (pl_targetable(ban, p.get_x(), y, &points)) {
		y--;
	}

	return points;
}

//角のwcm関数
std::vector<Point> pl_kaku_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.get_x() - 1, y = p.get_y() - 1;
	/*
	*右上方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x--;
		y--;
	}

	x = p.get_x() + 1;
	y = p.get_y() - 1;
	/*
	*左上方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x++;
		y--;
	}

	x = p.get_x() - 1;
	y = p.get_y() + 1;
	/*
	*右下方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x--;
		y++;
	}

	x = p.get_x() + 1;
	y = p.get_y() + 1;
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

	u8_t x = p.get_x(), y = p.get_y();

	//前方方向の移動可能判定
	pl_targetable(ban, x, p.get_y() - 1, &points);
	pl_targetable(ban, x - 1, p.get_y() - 1, &points);
	pl_targetable(ban, x + 1, p.get_y() - 1, &points);

	//横方向の移動可能判定
	pl_targetable(ban, x + 1, p.get_y(), &points);
	pl_targetable(ban, x - 1, p.get_y(), &points);

	//後方方向の移動可能判定
	pl_targetable(ban, x, p.get_y() + 1, &points);
	pl_targetable(ban, x - 1, p.get_y() + 1, &points);
	pl_targetable(ban, x + 1, p.get_y() + 1, &points);

	return points;
}

//龍のwcm関数
std::vector<Point> pl_ryu_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;
	u8_t x = p.get_x() - 1, y;

	/*
	*左方向の移動可能判定
	*/
	while (pl_targetable(ban, x, p.get_y(), &points)) {
		x--;
	}

	/*
	*左方向の移動可能判定
	*/
	x = p.get_x() + 1;
	while (pl_targetable(ban, x, p.get_y(), &points)) {
		x++;
	}

	/*
	*下方向の移動可能判定
	*/
	y = p.get_y() + 1;
	while (pl_targetable(ban, p.get_x(), y, &points)) {
		y++;
	}

	/*
	*上方向の移動可能判定
	*/
	y = p.get_y() - 1;
	while (pl_targetable(ban, p.get_x(), y, &points)) {
		y--;
	}

	x = p.get_x();
	y = p.get_y();
	//斜め上方向の移動可能判定
	pl_targetable(ban, x - 1, p.get_y() - 1, &points);
	pl_targetable(ban, x + 1, p.get_y() - 1, &points);

	//斜め下方向の移動可能判定
	pl_targetable(ban, x - 1, p.get_y() + 1, &points);
	pl_targetable(ban, x + 1, p.get_y() + 1, &points);

	return points;
}

//馬のwcm関数
std::vector<Point> pl_uma_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.get_x() - 1, y = p.get_y() - 1;
	/*
	*右上方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x--;
		y--;
	}

	x = p.get_x() + 1;
	y = p.get_y() - 1;
	/*
	*左上方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x++;
		y--;
	}

	x = p.get_x() - 1;
	y = p.get_y() + 1;
	/*
	*右下方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x--;
		y++;
	}

	x = p.get_x() + 1;
	y = p.get_y() + 1;
	/*
	*右下方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x++;
		y++;
	}

	x = p.get_x();
	y = p.get_y();
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
	ai_targetable(ban, point.get_x(), point.get_y() + 1, &points);
	

	return points;
}

//敵の香車のwcm関数
std::vector<Point> ai_kyousha_wcm(KOMA_TYPE **ban, Point point) {
	std::vector<Point> points;

	u8_t y = point.get_y() + 1;
	while (ai_targetable(ban, point.get_x(), y, &points)) {
		y++;
	}
	return points;
}

//敵の桂馬のwcm関数
std::vector<Point> ai_keima_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	ai_targetable(ban, p.get_x() + 1, p.get_y() + 2, &points);
	ai_targetable(ban, p.get_x() - 1, p.get_y() + 2, &points);

	return points;
}

//敵の銀のwcm関数
std::vector<Point> ai_gin_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	/*
	*前方方向の移動可能判定
	*/
	ai_targetable(ban, p.get_x() - 1, p.get_y() + 1, &points);
	ai_targetable(ban, p.get_x(), p.get_y() + 1, &points);
	ai_targetable(ban, p.get_x() + 1, p.get_y() + 1, &points);

	/*
	*後方方向の移動可能判定
	*/
	ai_targetable(ban, p.get_x() - 1, p.get_y() - 1, &points);
	ai_targetable(ban, p.get_x() + 1, p.get_y() - 1, &points);

	return points;
}

//敵の金のwcm関数
std::vector<Point> ai_kin_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	/*
	*前方方向の移動可能判定
	*/
	ai_targetable(ban, p.get_x() - 1, p.get_y() + 1, &points);
	ai_targetable(ban, p.get_x(), p.get_y() + 1, &points);
	ai_targetable(ban, p.get_x() + 1, p.get_y() + 1, &points);

	/*
	*横方向の移動可能判定
	*/
	ai_targetable(ban, p.get_x() - 1, p.get_y(), &points);
	ai_targetable(ban, p.get_x() + 1, p.get_y(), &points);

	/*
	*後方方向の移動可能判定
	*/
	ai_targetable(ban, p.get_x(), p.get_y() - 1, &points);

	return points;
}

//敵の飛車のwcm関数
std::vector<Point> ai_hisha_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;
	int x = p.get_x() - 1, y;

	/*
	*左方向の移動可能判定
	*/
	while (ai_targetable(ban, x, p.get_y(), &points)) {
		x--;
	}

	/*
	*左方向の移動可能判定
	*/
	x = p.get_x() + 1;
	while (ai_targetable(ban, x, p.get_y(), &points)) {
		x++;
	}

	/*
	*下方向の移動可能判定
	*/
	y = p.get_y() - 1;
	while (ai_targetable(ban, p.get_x(), y, &points)) {
		y--;
	}

	/*
	*上方向の移動可能判定
	*/
	y = p.get_y() + 1;
	while (ai_targetable(ban, p.get_x(), y, &points)) {
		y++;
	}

	return points;
}

//敵の角のwcm関数
std::vector<Point> ai_kaku_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	i8_t x = p.get_x() - 1, y = p.get_y() - 1;
	/*
	*右上方向の移動可能判定
	*/
	while (ai_targetable(ban, x, y, &points)) {
		x--;
		y--;
	}

	x = p.get_x() + 1;
	y = p.get_y() - 1;
	/*
	*左上方向の移動可能判定
	*/
	while (ai_targetable(ban, x, y, &points)) {
		x++;
		y--;
	}

	x = p.get_x() - 1;
	y = p.get_y() + 1;
	/*
	*右下方向の移動可能判定
	*/
	while (ai_targetable(ban, x, y, &points)) {
		x--;
		y++;
	}

	x = p.get_x() + 1;
	y = p.get_y() + 1;
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
	ai_targetable(ban, p.get_x(), p.get_y() - 1, &points);
	ai_targetable(ban, p.get_x() - 1, p.get_y() - 1, &points);
	ai_targetable(ban, p.get_x() + 1, p.get_y() - 1, &points);

	//横方向の移動可能判定
	ai_targetable(ban, p.get_x() + 1, p.get_y(), &points);
	ai_targetable(ban, p.get_x() - 1, p.get_y(), &points);

	//後方方向の移動可能判定
	ai_targetable(ban, p.get_x(), p.get_y() + 1, &points);
	ai_targetable(ban, p.get_x() - 1, p.get_y() + 1, &points);
	ai_targetable(ban, p.get_x() + 1, p.get_y() + 1, &points);

	return points;
}


//龍のwcm関数
std::vector<Point> ai_ryu_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;
	int x = p.get_x() - 1, y;

	/*
	*左方向の移動可能判定
	*/
	while (pl_targetable(ban, x, p.get_y(), &points)) {
		x--;
	}

	/*
	*左方向の移動可能判定
	*/
	x = p.get_x() + 1;
	while (pl_targetable(ban, x, p.get_y(), &points)) {
		x++;
	}

	/*
	*下方向の移動可能判定
	*/
	y = p.get_y() + 1;
	while (pl_targetable(ban, p.get_x(), y, &points)) {
		y++;
	}

	/*
	*上方向の移動可能判定
	*/
	y = p.get_y() - 1;
	while (pl_targetable(ban, p.get_x(), y, &points)) {
		y--;
	}

	//斜め上方向の移動可能判定
	pl_targetable(ban, p.get_x() - 1, p.get_y() - 1, &points);
	pl_targetable(ban, p.get_x() + 1, p.get_y() - 1, &points);

	//斜め下方向の移動可能判定
	pl_targetable(ban, p.get_x() - 1, p.get_y() + 1, &points);
	pl_targetable(ban, p.get_x() + 1, p.get_y() + 1, &points);

	return points;
}

//馬のwcm関数
std::vector<Point> ai_uma_wcm(KOMA_TYPE **ban, Point p) {
	std::vector<Point> points;

	int x = p.get_x() - 1, y = p.get_y() - 1;
	/*
	*右上方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x--;
		y--;
	}

	x = p.get_x() + 1;
	y = p.get_y() - 1;
	/*
	*左上方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x++;
		y--;
	}

	x = p.get_x() - 1;
	y = p.get_y() + 1;
	/*
	*右下方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x--;
		y++;
	}

	x = p.get_x() + 1;
	y = p.get_y() + 1;
	/*
	*右下方向の移動可能判定
	*/
	while (pl_targetable(ban, x, y, &points)) {
		x++;
		y++;
	}

	//横方向の移動可能判定
	pl_targetable(ban, p.get_x() + 1, p.get_y(), &points);
	pl_targetable(ban, p.get_x() - 1, p.get_y(), &points);

	//前方の移動可能判定
	pl_targetable(ban, p.get_x(), p.get_y() - 1, &points);

	//後方方向の移動可能判定
	pl_targetable(ban, p.get_x(), p.get_y() + 1, &points);

	return points;

}

//手駒のwcm関数
std::vector<Point> tegoma_wcm(KOMA_TYPE **main_ban, Point p) {
	std::vector<Point> points;
	for (int y = 0; y < 9; y++)
		for (int x = 0; x < 9; x++)
			if (main_ban[x][y] == EMPTY)
				points.push_back(Point(std::abs(x - 9), y + 1));
	return points;
}

//打つときに、二歩にならないためのwcm関数
std::vector<Point> nihu_wcm(KOMA_TYPE **main_ban) {
	std::vector<Point> points;
	bool nihu = false;

	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
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
				if (main_ban[x][y] == EMPTY && main_ban[x][y - 1] != EN_OU) {
					points.push_back(Point(std::abs(x - 9), y + 1));
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

	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
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
			for (int y = 0; y < 8; y++) {
				if (main_ban[x][y] == EMPTY && main_ban[x][y + 1] != OU) {
					points.push_back(Point(std::abs(x - 9), y + 1));
				}
			}
		}
		nihu = false;
	}

	return points;
}

u8_t is_player_koma(KOMA_TYPE type){
	return (type >= HU && type <= OU);
}

u8_t is_ai_koma(KOMA_TYPE type){
	return (type >= EN_HU && type <= EN_OU);
}

u8_t ai_targetable(KOMA_TYPE **ban, u8_t x, u8_t y, std::vector<Point>  *points){

	//盤面外なのでだめ
	if(x < 0 || x > 8 || y < 0 || y > 8){
		return false;
	}

	//EMPTYなので、特に制限はない
	if(ban[x][y] == EMPTY){
		points->push_back(Point(x, y));
		return true;
	}

	//プレイヤーの駒なので、取ることができる
	if(is_player_koma(ban[x][y])){
		points->push_back(Point(x, y));
		return false;
	}

	//自分の駒（AI）なので、移動することはできない
	if(is_ai_koma(ban[x][y])){
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
	if(ban[x][y] == EMPTY){
		points->push_back(Point(x, y));
		return true;
	}

	//AIの駒なので、取ることができる
	if(is_ai_koma(ban[x][y])){
		points->push_back(Point(x, y));
		return false;
	}

	//相手（プレイヤー）なので、移動することはできない
	if(is_player_koma(ban[x][y])){
		return false;
	}
}
