﻿#ifndef _TYPES_HPP
#define _TYPES_HPP

#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <sstream>
#include <functional>
#include <unordered_map>
#include <mutex>

using u8_t = std::uint_fast8_t;
using u16_t = std::uint_fast16_t;
using u32_t = std::uint_fast32_t;
using u64_t = std::uint_fast64_t;

using i8_t = std::int_fast8_t;
using i16_t = std::int_fast16_t;
using i32_t = std::int_fast32_t;
using i64_t = std::int_fast64_t;

using KOMA_TYPE = u8_t;

/*
* ビット演算による駒の判別のためのID
*
* LSBはプレイヤーの駒か、見方の細かを判別するためのビット。PLAYER_SとAI_COYURI_Sを使ってアンド演算等で判定
* 
* 
*
*/
#define PLAYER_S         0b00000000
#define AI_COYURI_S      0b00000001
#define AI_TO_PLAYER_DEF 0b11111110

/*下位からの定義　　
1:   0->プレイヤー    1->AI
2~6: 配列で表したときのインデックス
7,8:   未定
*/
#define EMPTY       0b00000000
#define HU          0b00000010
#define KYOUSHA     0b00000100
#define KEIMA       0b00000110
#define GIN         0b00001000
#define KIN         0b00001010
#define HISHA       0b00001100
#define KAKU        0b00001110
#define TOKIN       0b00010000
#define NARIKYOU    0b00010010
#define NARIKEI     0b00010100
#define NARIGIN     0b00010110
#define RYU         0b00011000
#define UMA         0b00011010
#define OU			0b00011100
#define EN_HU		0b00011111
#define EN_KYOUSHA	0b00100001
#define EN_KEIMA	0b00100011
#define EN_GIN		0b00100101
#define EN_KIN		0b00100111
#define EN_HISHA	0b00101001
#define EN_KAKU		0b00101011
#define EN_TOKIN	0b00101101
#define EN_NARIKYOU	0b00101111
#define EN_NARIKEI	0b00110001
#define EN_NARIGIN	0b00110011
#define EN_RYU		0b00110101
#define EN_UMA		0b00110111
#define EN_OU		0b00111001

static KOMA_TYPE convert_array[] = {
	EMPTY,
	EMPTY,
	HU,
	KYOUSHA,
	KEIMA,
	GIN,
	KIN,
	HISHA,
	KAKU,
	TOKIN,
	NARIKYOU,
	NARIKEI,
	NARIGIN,
	RYU,
	UMA,
	OU,
	EN_HU,
	EN_KYOUSHA,
	EN_KEIMA,
	EN_GIN,
	EN_KIN,
	EN_HISHA,
	EN_KAKU,
	EN_TOKIN,
	EN_NARIKYOU,
	EN_NARIKEI,
	EN_NARIGIN,
	EN_RYU,
	EN_UMA,
	EN_OU,
};

static KOMA_TYPE reset_and_negari_array[] = {
	EMPTY,
	EN_HU,
	EN_KYOUSHA,
	EN_KEIMA,
	EN_GIN,
	EN_KIN,
	EN_HISHA,
	EN_KAKU,
	EN_HU,
	EN_KYOUSHA,
	EN_KEIMA,
	EN_GIN,
	EN_HISHA,
	EN_KAKU,
	EN_OU,
	HU,
	KYOUSHA,
	KEIMA,
	GIN,
	KIN,
	HISHA,
	KAKU,
	HU,
	KYOUSHA,
	KEIMA,
	GIN,
	HISHA,
	KAKU,
	OU
};

#define _NEGAERI(type) ( reset_and_negari_array[type >> 1] )
#define _IS_EMPTY(type) (!type)
#define _IS_NOT_EMPTY(type) (type)
#define _EQUALS(type1, type2) (type1 == type2)
#define _IS_AI_KOMA(type) (type & AI_COYURI_S)
#define _IS_PLAYER_KOMA(type) ( !(type & AI_COYURI_S) )
#define _KOMA_TO_INDEX(type) (type >> 1)

using MochiGoma = std::vector<KOMA_TYPE>;

class Point {

public:
	/*
	*座標の位置を保持する変数
	*/
	u8_t x : 4;
	u8_t y : 4;

	Point(u8_t x, u8_t y) {
		this->x = x;
		this->y = y;
	}
};

#define _point_error_check(p) (p.x < 0 || p.x > 8 || p.y < 0 || p.y > 8)
#define _point_xy_error_check(x, y) (x >= 0 && x <= 8 && y >= 0 && y <= 8)

#define _MOCHIGOMA_LIMIT 38

using scalar_point = u8_t;
#define _create_scalar_point(x, y) ((x + 1) + ((y + 1) * 11))
#define _scalar_point_within_ai_zone(_sc_pt) (_sc_pt < 44)
#define _scalar_point_within_pl_zone(_sc_pt) (_sc_pt > 76)


class BANMEN {
	KOMA_TYPE **banmen;

public:
	BANMEN();
	~BANMEN();
	KOMA_TYPE get_type(u8_t x, u8_t y);
	void set_type(u8_t x, u8_t y, KOMA_TYPE type);
	void copy_banmen(BANMEN *original);
	KOMA_TYPE **get_banmen();

};

#define _AI_TURN		0
#define _PLAYER_TURN	1

#define _NEXT_TURN(turn) ( turn ^ 1 )
#define _IS_AI_TURN(turn) ( !turn )


/*
*Point28の構造
*最上位ビットから下に4bit分 -> y座標
*最下位ビットから上に4bit分 -> x座標
*/
using Point2d8 = std::uint_fast8_t;
#define _point2d8_create(x, y) ( (y << 4) | x )
#define _point2d8_get_y(_point28) ( _point28 >> 4 )
#define _point2d8_get_x(_point28) ( (_point28 << 4) >> 4 )

/*
*PiPの構造
*MSBから
*1~4bit
*Y座標
*5~8bit
*X座標
*9~16bit
*駒のタイプ
*/
using PiP = u16_t;
#define _pip_create(x, y, type) ( ( ( (y << 4) | x ) << 8 ) | type )
#define _pip_get_y(_pip) (_pip >> 12)
#define _pip_get_x(_pip) ((_pip << 4) >> 12)
#define _pip_get_type(_pip) ((_pip << 8) >> 8)


class MochiGomaGroup {

	/*
	*持ち駒の枚数だけ保持しておけば良いのでは？
	*KOMA_TYPE -> 駒  u8_t -> 枚数
	*/
	std::unordered_map<KOMA_TYPE, u8_t> mochi_goma;

public:
	MochiGomaGroup(u8_t flag);
	void insert(KOMA_TYPE _type);
	void pop(KOMA_TYPE _type);
	u8_t get(KOMA_TYPE _type);

};

#define _AI_MOCHIGOMA_FLAG 0
#define _PL_MOCHIGOMA_FLAG 1

class Node {

	BANMEN *banmen;
	Node *parent;
	std::vector<Node *> children;

public:

	MochiGoma *ai_mochigoma;
	MochiGoma *pl_mochigoma;
	
	u8_t  turn;
	i64_t evalue;
	Point ai_ou_point;
	Point pl_ou_point;

	Node(BANMEN *ban, Node *pare, MochiGoma *ai_mochi, MochiGoma *pl_mochi);
	Node(BANMEN *ban, Node *pare, MochiGoma *ai_mochi, MochiGoma *pl_mochi, u8_t turn_arg, Point arg_ai_ou_point, Point arg_pl_ou_point);
	Node(BANMEN *ban, Node *pare);
	Node *get_parent();
	Node *clone();
	~Node();
	BANMEN *get_banmen();
	std::vector<Node *> & get_children();
	i64_t get_evalue();
	void set_evalue(int value);
	void delete_children();

};

class CoyuriNegaScout {

private:
	Node *root;
	Node *result;
	i64_t nega_scout_search(Node *node, i64_t alpha, i64_t beta, u8_t limit);
	std::function<i64_t(Node *)> eval;
	u64_t tesuu;
	u64_t search_depth;
	bool ai_en_oute_check(Node *node);
	bool pl_oute_check(Node *node);
	void use_first_jouseki();
	Node *pl_ou_tsumi_check();
	bool main_search_fin;
	std::mutex tsumi_check_mutex;
	static bool compare_1_less_than_2(Node *_node1, Node *_node2) {
		return _node1->evalue < _node2->evalue;
	}

	static bool compare_1_bigger_than_2(Node *_node1, Node *_node2) {
		return _node1->evalue > _node2->evalue;
	}
	bool is_fin_main_search() {
		std::lock_guard<std::mutex> lock(this->tsumi_check_mutex);
		return this->main_search_fin;
	}
	void finish_main_search() {
		std::lock_guard<std::mutex> lock(this->tsumi_check_mutex);
		this->main_search_fin = true;
	}

public:
	CoyuriNegaScout(Node *node, u64_t tesuu);
	void start();
	void print(const char *file_name);
	bool & ref_main_search_fin() {
		std::lock_guard<std::mutex> lock(this->tsumi_check_mutex);
		return this->main_search_fin;
	}
};

inline MochiGoma *clone_mochigoma(MochiGoma *source) {
	u8_t size, i;
	MochiGoma *uketori = new MochiGoma(size = source->size());
	for (i = 0; i < size; ++i) {
		uketori->at(i) = source->at(i);
	}
	return uketori;
}


class FileLoader {

private:

	void load_mochi(MochiGoma *mochi, std::string data) {
		std::stringstream ss(data);
		std::string s;
		std::getline(ss, s, ' ');

		while (std::getline(ss, s, ' ')) {
			mochi->push_back(convert_array[std::stoi(s)]);
		}
	}

public:
	Node *load_file(const char *file_name, u64_t *teban_num) {

		BANMEN *ban = new BANMEN;
		MochiGoma *ai_mochi = new MochiGoma, *pl_mochi = new MochiGoma;
		Point ai_ou(0, 0), pl_ou(0, 0);
		KOMA_TYPE type;

		i64_t i_t_i;
		std::ifstream ifs(file_name);
		if (ifs.fail()) {
			puts("FAILD");
			exit(0);
		}
		std::string str;

		std::getline(ifs, str);
		*teban_num = std::stoi(str);


		for (u8_t y = 0; y < 9; ++y) {
			std::getline(ifs, str);
			std::stringstream ss(str);

			for (u8_t x = 0; x < 9; ++x) {
				ss >> i_t_i;
				ban->set_type(x, y, type = convert_array[i_t_i]);
				if (_EQUALS(type, OU))
				{
					pl_ou.x = x;
					pl_ou.y = y;
				}
				else if(_EQUALS(type, EN_OU))
				{
					ai_ou.x = x;
					ai_ou.y = y;
				}
			}
		}

		std::getline(ifs, str);
		load_mochi(ai_mochi, str);

		std::getline(ifs, str);
		load_mochi(pl_mochi, str);

		return new Node(ban, nullptr, ai_mochi, pl_mochi, _AI_TURN, ai_ou, pl_ou);
	}
};

class CoyuriIniter {

private:
	FileLoader file_loader;

public:
	void init(const char *file_name, Node **node, u64_t *teban_num) {
		*node = file_loader.load_file(file_name, teban_num);
	}

};

#endif