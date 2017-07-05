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
std::vector<Point> null_wcm(BANMEN *ban, Point p) {
	std::vector<Point> points;
	return points;
}

//歩のwcm関数
std::vector<Point> pl_hu_wcm(BANMEN *ban, Point point) {
	std::vector<Point> points;

	/*
	*一つ前方を確認
	*/
	pl_targetable(ban, point.x, point.y - 1, &points);

	return points;
}

std::vector<Point> pl_kyousha_wcm(BANMEN *ban, Point point) {
	std::vector<Point> points;

	u8_t x = point.x, y = point.y;

	do {
		--y;
	} while (pl_targetable(ban, x, y, &points));

	return points;
}

//桂馬のwcm関数
std::vector<Point> pl_keima_wcm(BANMEN *ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x, y = p.y;

	/*
	*２つ前に進めない位置にいる場合移動できない
	*/
	if (y < 2) {
		return points;
	}

	pl_targetable(ban, x + 1, y - 2, &points);
	pl_targetable(ban, x - 1, y - 2, &points);

	return points;
}

//銀のwcm関数
std::vector<Point> pl_gin_wcm(BANMEN *ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x, y = p.y - 1;

	/*
	*前方方向の移動可能判定
	*/
	pl_targetable(ban, x - 1, y, &points);
	pl_targetable(ban, x, y, &points);
	pl_targetable(ban, x + 1, y, &points);

	y += 2;

	/*
	*後方方向の移動可能判定
	*/
	pl_targetable(ban, x - 1, y, &points);
	pl_targetable(ban, x + 1, y, &points);

	return points;
}

//銀のwcm関数
std::vector<Point> pl_kin_wcm(BANMEN *ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x, y = p.y - 1;

	/*
	*前方方向の移動可能判定
	*/
	pl_targetable(ban, x - 1, y, &points);
	pl_targetable(ban, x, y, &points);
	pl_targetable(ban, x + 1, y, &points);

	/*
	*横方向の移動可能判定
	*/
	++y;
	pl_targetable(ban, x - 1, y, &points);
	pl_targetable(ban, x + 1, y, &points);

	/*
	*後方方向の移動可能判定
	*/
	++y;
	pl_targetable(ban, x, y, &points);

	return points;
}

//飛車のwcm関数
std::vector<Point> pl_hisha_wcm(BANMEN *ban, Point p) {
	std::vector<Point> points;
	u8_t x = p.x, y = p.y;

	/*
	*左方向の移動可能判定
	*/
	do {
		--x;
	} while (pl_targetable(ban, x, y, &points));

	/*
	*左方向の移動可能判定
	*/
	x = p.x;
	do {
		++x;
	} while (pl_targetable(ban, x, y, &points));

	/*
	*下方向の移動可能判定
	*/
	y = p.y;
	x = p.x;
	do {
		++y;
	} while (pl_targetable(ban, x, y, &points));

	/*
	*上方向の移動可能判定
	*/
	y = p.y;
	do {
		--y;
	} while (pl_targetable(ban, x, y, &points));

	return points;
}

//角のwcm関数
std::vector<Point> pl_kaku_wcm(BANMEN *ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x, y = p.y;
	/*
	*右上方向の移動可能判定
	*/
	do {
		--x;
		--y;
	} while (pl_targetable(ban, x, y, &points));

	x = p.x;
	y = p.y;
	/*
	*左上方向の移動可能判定
	*/
	do {
		++x;
		--y;
	} while (pl_targetable(ban, x, y, &points));

	x = p.x;
	y = p.y;
	/*
	*右下方向の移動可能判定
	*/
	do {
		--x;
		++y;
	} while (pl_targetable(ban, x, y, &points));

	x = p.x;
	y = p.y;
	/*
	*右下方向の移動可能判定
	*/
	do {
		++x;
		++y;
	} while (pl_targetable(ban, x, y, &points));

	return points;
}

//王将のwcm関数
std::vector<Point> pl_ou_wcm(BANMEN *ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x, y = p.y - 1;

	//前方方向の移動可能判定
	pl_targetable(ban, x, y, &points);
	pl_targetable(ban, x - 1, y, &points);
	pl_targetable(ban, x + 1, y, &points);

	//横方向の移動可能判定
	++y;
	pl_targetable(ban, x + 1, y, &points);
	pl_targetable(ban, x - 1, y, &points);

	//後方方向の移動可能判定
	++y;
	pl_targetable(ban, x, y, &points);
	pl_targetable(ban, x - 1, y, &points);
	pl_targetable(ban, x + 1, y, &points);

	return points;
}

//龍のwcm関数
std::vector<Point> pl_ryu_wcm(BANMEN *ban, Point p) {
	std::vector<Point> points;
	
	u8_t x = p.x, y = p.y;
	/*
	*左方向の移動可能判定
	*/
	do {
		--x;
	} while (pl_targetable(ban, x, y, &points));

	/*
	*左方向の移動可能判定
	*/
	x = p.x;
	do {
		++x;
	} while (pl_targetable(ban, x, y, &points));

	/*
	*下方向の移動可能判定
	*/
	y = p.y;
	x = p.x;
	do {
		++y;
	} while (pl_targetable(ban, x, y, &points));

	/*
	*上方向の移動可能判定
	*/
	y = p.y;
	do {
		--y;
	} while (pl_targetable(ban, x, y, &points));

	x = p.x;
	y = p.y;
	--y;
	//斜め上方向の移動可能判定
	pl_targetable(ban, x - 1, y, &points);
	pl_targetable(ban, x + 1, y, &points);

	//斜め下方向の移動可能判定
	y += 2;
	pl_targetable(ban, x - 1, y, &points);
	pl_targetable(ban, x + 1, y, &points);

	return points;
}

//馬のwcm関数
std::vector<Point> pl_uma_wcm(BANMEN *ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x, y = p.y;
	/*
	*右上方向の移動可能判定
	*/
	do {
		--x;
		--y;
	} while (pl_targetable(ban, x, y, &points));

	x = p.x;
	y = p.y;
	/*
	*左上方向の移動可能判定
	*/
	do {
		++x;
		--y;
	} while (pl_targetable(ban, x, y, &points));

	x = p.x;
	y = p.y;
	/*
	*右下方向の移動可能判定
	*/
	do {
		--x;
		++y;
	} while (pl_targetable(ban, x, y, &points));

	x = p.x;
	y = p.y;
	/*
	*右下方向の移動可能判定
	*/
	do {
		++x;
		++y;
	} while (pl_targetable(ban, x, y, &points));

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
std::vector<Point> ai_hu_wcm(BANMEN *ban, Point point) {
	std::vector<Point> points;

	/*
	*一つ前方を確認
	*/
	ai_targetable(ban, point.x, point.y + 1, &points);
	

	return points;
}

//敵の香車のwcm関数
std::vector<Point> ai_kyousha_wcm(BANMEN *ban, Point point) {
	std::vector<Point> points;

	u8_t x = point.x, y = point.y;
	do {
		++y;
	} while (ai_targetable(ban, x, y, &points));
	return points;
}

//敵の桂馬のwcm関数
std::vector<Point> ai_keima_wcm(BANMEN *ban, Point p) {
	std::vector<Point> points;

	if (p.y > 6) {
		return points;
	}

	ai_targetable(ban, p.x + 1, p.y + 2, &points);
	ai_targetable(ban, p.x - 1, p.y + 2, &points);

	return points;
}

//敵の銀のwcm関数
std::vector<Point> ai_gin_wcm(BANMEN *ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x, y = p.y;
	++y;

	/*
	*前方方向の移動可能判定
	*/
	ai_targetable(ban, x - 1, y, &points);
	ai_targetable(ban, x, y, &points);
	ai_targetable(ban, x + 1, y, &points);

	/*
	*後方方向の移動可能判定
	*/
	y -= 2;
	ai_targetable(ban, x - 1, y, &points);
	ai_targetable(ban, x + 1, y, &points);

	return points;
}

//敵の金のwcm関数
std::vector<Point> ai_kin_wcm(BANMEN *ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x, y = p.y;
	++y;

	/*
	*前方方向の移動可能判定
	*/
	ai_targetable(ban, x - 1, y, &points);
	ai_targetable(ban, x, y, &points);
	ai_targetable(ban, x + 1, y, &points);

	/*
	*横方向の移動可能判定
	*/
	--y;
	ai_targetable(ban, x - 1, y, &points);
	ai_targetable(ban, x + 1, y, &points);

	/*
	*後方方向の移動可能判定
	*/
	--y;
	ai_targetable(ban, x, y, &points);

	return points;
}

//敵の飛車のwcm関数
std::vector<Point> ai_hisha_wcm(BANMEN *ban, Point p) {
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
std::vector<Point> ai_kaku_wcm(BANMEN *ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x, y = p.y;
	/*
	*右上方向の移動可能判定
	*/
	do {
		--x;
		--y;
	} while (ai_targetable(ban, x, y, &points));

	x = p.x;
	y = p.y;
	/*
	*左上方向の移動可能判定
	*/
	do {
		++x;
		--y;
	} while (ai_targetable(ban, x, y, &points));

	x = p.x;
	y = p.y;
	/*
	*右下方向の移動可能判定
	*/
	do {
		--x;
		++y;
	} while (ai_targetable(ban, x, y, &points));

	x = p.x;
	y = p.y;
	/*
	*右下方向の移動可能判定
	*/
	do {
		++x;
		++y;
	} while (ai_targetable(ban, x, y, &points));

	return points;
}

//敵の王将のwcm関数
std::vector<Point> ai_ou_wcm(BANMEN *ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x, y = p.y;
	--y;

	//前方方向の移動可能判定
	ai_targetable(ban, x, y, &points);
	ai_targetable(ban, x - 1, y, &points);
	ai_targetable(ban, x + 1, y, &points);

	//横方向の移動可能判定
	++y;
	ai_targetable(ban, x + 1, y, &points);
	ai_targetable(ban, x - 1, y, &points);

	//後方方向の移動可能判定
	++y;
	ai_targetable(ban, x, y, &points);
	ai_targetable(ban, x - 1, y, &points);
	ai_targetable(ban, x + 1, y, &points);

	return points;
}


//龍のwcm関数
std::vector<Point> ai_ryu_wcm(BANMEN *ban, Point p) {
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


	y = p.y;

	//斜め上方向の移動可能判定
	ai_targetable(ban, x - 1, y - 1, &points);
	ai_targetable(ban, x + 1, y - 1, &points);

	//斜め下方向の移動可能判定
	ai_targetable(ban, x - 1, y + 1, &points);
	ai_targetable(ban, x + 1, y + 1, &points);

	return points;
}

//馬のwcm関数
std::vector<Point> ai_uma_wcm(BANMEN *ban, Point p) {
	std::vector<Point> points;

	u8_t x = p.x, y = p.y;
	/*
	*右上方向の移動可能判定
	*/
	do {
		--x;
		--y;
	} while (ai_targetable(ban, x, y, &points));

	x = p.x;
	y = p.y;
	/*
	*左上方向の移動可能判定
	*/
	do {
		++x;
		--y;
	} while (ai_targetable(ban, x, y, &points));

	x = p.x;
	y = p.y;
	/*
	*右下方向の移動可能判定
	*/
	do {
		--x;
		++y;
	} while (ai_targetable(ban, x, y, &points));

	x = p.x;
	y = p.y;
	/*
	*右下方向の移動可能判定
	*/
	do {
		++x;
		++y;
	} while (ai_targetable(ban, x, y, &points));

	x = p.x;
	y = p.y;
	//横方向の移動可能判定
	ai_targetable(ban, x + 1, y, &points);
	ai_targetable(ban, x - 1, y, &points);

	//前方の移動可能判定
	ai_targetable(ban, x, y - 1, &points);

	//後方方向の移動可能判定
	ai_targetable(ban, x, y + 1, &points);

	return points;

}

//手駒のwcm関数
std::vector<Point> tegoma_wcm(BANMEN *main_ban, Point p) {
	std::vector<Point> points;
	for (u8_t y = 0; y < 9; y++) {
		for (u8_t x = 0; x < 9; x++) {
			if (_IS_EMPTY(main_ban->get_type(x, y))) {
				points.push_back(Point(x, y));
			}
		}
	}
	return points;
}

//打つときに、二歩にならないためのwcm関数
std::vector<Point> nihu_wcm(BANMEN *main_ban) {
	std::vector<Point> points;
	bool nihu = false;

	for (u8_t x = 0; x < 9; x++) {
		for (u8_t y = 0; y < 9; y++) {
			if (main_ban->get_type(x, y) == HU) {
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
				if (_IS_EMPTY(main_ban->get_type(x, y))) {
					points.push_back(Point(x, y));
				}
			}
		}
		nihu = false;
	}

	return points;
}

//打つときに、二歩にならないためのwcm関数(ai用)
std::vector<Point> ai_nihu_wcm(BANMEN *main_ban) {
	std::vector<Point> points;
	bool nihu = false;

	for (u8_t x = 0; x < 9; x++) {
		for (u8_t y = 0; y < 9; y++) {
			if (main_ban->get_type(x, y) == EN_HU) {
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
				if (_IS_EMPTY(main_ban->get_type(x, y))) {
					points.push_back(Point(x, y));
				}
			}
		}
		nihu = false;
	}

	return points;
}

/*
*前にしか動けない駒の禁じてを防ぐwcm
*/
std::vector<Point> ai_mochi_keima_wcm(BANMEN *main_ban) {
	std::vector<Point> points;

	for (u8_t y = 0; y < 7; y++) {
		for (u8_t x = 0; x < 9; x++) {
			if (_IS_EMPTY(main_ban->get_type(x, y))) {
				points.push_back(Point(x, y));
			}
		}
	}

	return points;
}


/*
*前にしか動けない駒の禁じてを防ぐwcm
*/
std::vector<Point> ai_mochi_kyousha_wcm(BANMEN *main_ban) {
	std::vector<Point> points;

	for (u8_t y = 0; y < 8; y++) {
		for (u8_t x = 0; x < 9; x++) {
			if (_IS_EMPTY(main_ban->get_type(x, y))) {
				points.push_back(Point(x, y));
			}
		}
	}

	return points;
}

/*
*前にしか動けない駒の禁じてを防ぐwcm
*/
std::vector<Point> pl_mochi_keima_wcm(BANMEN *main_ban) {
	std::vector<Point> points;

	for (u8_t y = 2; y < 9; y++) {
		for (u8_t x = 0; x < 9; x++) {
			if (_IS_EMPTY(main_ban->get_type(x, y))) {
				points.push_back(Point(x, y));
			}
		}
	}

	return points;
}


/*
*前にしか動けない駒の禁じてを防ぐwcm
*/
std::vector<Point> pl_mochi_kyousha_wcm(BANMEN *main_ban) {
	std::vector<Point> points;

	for (u8_t y = 1; y < 9; y++) {
		for (u8_t x = 0; x < 9; x++) {
			if (_IS_EMPTY(main_ban->get_type(x, y))) {
				points.push_back(Point(x, y));
			}
		}
	}

	return points;
}

u8_t ai_targetable(BANMEN *ban, u8_t x, u8_t y, std::vector<Point>  *points){

	//盤面外なのでだめ
	if(x < 0 || x > 8 || y < 0 || y > 8){
		return false;
	}

	//EMPTYなので、特に制限はない
	if(_IS_EMPTY(ban->get_type(x, y))){
		points->push_back(Point(x, y));
		return true;
	}

	//プレイヤーの駒なので、取ることができる
	if(_IS_EMPTY(ban->get_type(x, y))){
		points->push_back(Point(x, y));
		return false;
	}

	//自分の駒（AI）なので、移動することはできない
	if(_IS_EMPTY(ban->get_type(x, y))){
		return false;
	}

	return false;
}

u8_t pl_targetable(BANMEN *ban, u8_t x, u8_t y, std::vector<Point>  *points){
      //盤面外なのでだめ
	if(x < 0 || x > 8 || y < 0 || y > 8){
		return false;
	}

	//EMPTYなので、特に制限はない
	if(_IS_EMPTY(ban->get_type(x, y))){
		points->push_back(Point(x, y));
		return true;
	}

	//AIの駒なので、取ることができる
	if(_IS_EMPTY(ban->get_type(x, y))){
		points->push_back(Point(x, y));
		return false;
	}

	//相手（プレイヤー）なので、移動することはできない
	if(_IS_EMPTY(ban->get_type(x, y))){
		return false;
	}

	return false;
}
