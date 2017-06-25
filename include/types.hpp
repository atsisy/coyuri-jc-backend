#ifndef _TYPES_HPP
#define _TYPES_HPP

#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <sstream>
#include <functional>
#include "coutil.hpp"

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

/*
*Point28の構造
*最上位ビットから下に4bit分 -> y座標
*最下位ビットから上に4bit分 -> x座標
*/
using Point2d8 = std::uint_fast8_t;
#define _point2d8_create(y, x) ( (y << 4) | x )
#define _point2d8_get_x(point28) ( point28 >> 4 )
#define _point2d8_get_y(point28) ( (point28 << 4) >> 4 )

typedef struct {
	/*
	*座標の位置を保持する変数
	*/
	u8_t x : 4;
	u8_t y : 4;
} Point;

inline Point point(u8_t x, u8_t y) {
	Point p;
	p.x = x;
	p.y = y;
	return p;
}

#define _point_error_check(p) (p.x < 0 || p.x > 8 || p.y < 0 || p.y > 8)
#define _point_xy_error_check(x, y) (x >= 0 && x <= 8 && y >= 0 && y <= 8)

#define _MOCHIGOMA_LIMIT 38

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
	~Node();
	BANMEN *get_banmen();
	std::vector<Node *> & get_children();
	i64_t get_evalue();
	void set_evalue(int value);
	void delete_children();

};

struct PiP {
	KOMA_TYPE type;
	Point point;
	PiP(Point p, KOMA_TYPE t) { point = p; type = t; }
};

class CoyuriNegaScout {

private:
	Node *root;
	Node *result;
	i64_t nega_scout_search(Node *node, i64_t alpha, i64_t beta, u8_t limit);
	std::function<i64_t(Node *)> eval;
	u64_t tesuu;
	bool oute_check(BANMEN *ban);
	void use_first_jouseki();
	static bool compare_1_less_than_2(Node *_node1, Node *_node2) {
		return _node1->evalue < _node2->evalue;
	}

	static bool compare_1_bigger_than_2(Node *_node1, Node *_node2) {
		return _node1->evalue > _node2->evalue;
	}

public:
	CoyuriNegaScout(Node *node, u64_t tesuu);
	void start();
	void print(const char *file_name);

};

inline MochiGoma *clone_mochigoma(MochiGoma *source) {
	u8_t size, i;
	MochiGoma *uketori = new MochiGoma(size = source->size());
	for (i = 0; i < size; ++i) {
		uketori->at(i) = source->at(i);
	}
	return uketori;
}

struct Banmen {

	Point ai_ou_point;
	Point pl_ou_point;
	std::vector<PiP> ai_on;
	std::vector<PiP> pl_on;
	std::vector<PiP> ai_mochigoma;
	std::vector<PiP> pl_mochigoma;

	Banmen() {}
	Banmen(Banmen *ban) {
		u8_t size, i;
		size = ban->ai_on.size();
		for (i = 0; i < size; ++i) {
			ai_on.push_back(ban->ai_on.at(i));
		}

		size = ban->pl_on.size();
		for (i = 0; i < size; ++i) {
			pl_on.push_back(ban->pl_on.at(i));
		}

		size = ban->ai_mochigoma.size();
		for (i = 0; i < size; ++i) {
			ai_mochigoma.push_back(ban->ai_mochigoma.at(i));
		}

		size = ban->pl_mochigoma.size();
		for (i = 0; i < size; ++i) {
			pl_mochigoma.push_back(ban->ai_mochigoma.at(i));
		}
	}
};

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
		Point ai_ou, pl_ou;
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

struct Te {
	
public:
	Te(u8_t x, u8_t y, KOMA_TYPE type);
	Point point;
	KOMA_TYPE type;

};

class Jouseki {

private:

	template <typename _return_type>
	void load_json_elem(cut::json_parser & parser, std::string parent_key, std::string child_key, std::vector<_return_type>  *dish)
	{
		std::vector<std::string> iti_vector;
		iti_vector = parser.get_children(parent_key, child_key);
		for (std::string elem : iti_vector) {
			dish->push_back((_return_type)std::stoi(elem));
		}
	}

public:
	Jouseki(std::string file_name);
	std::vector<Te> jouseki_list;

};

#endif
