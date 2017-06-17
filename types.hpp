#ifndef _TYPES_HPP
#define _TYPES_HPP

#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <sstream>


using u8_t = std::uint_fast8_t;
using u16_t = std::uint_fast16_t;
using u32_t = std::uint_fast32_t;
using u64_t = std::uint_fast64_t;

using i8_t = std::int_fast8_t;
using i16_t = std::int_fast16_t;
using i32_t = std::int_fast32_t;
using i64_t = std::int_fast64_t;

using KOMA_TYPE = u64_t;

/*
* ビット演算による駒の判別のためのID
*
* LSBはプレイヤーの駒か、見方の細かを判別するためのビット。PLAYER_SとAI_COYURI_Sを使ってアンド演算等で判定
* 
* 
*
*/
#define PLAYER_S         0b0000000000000000000000000000000000000000000000000000000000000000
#define AI_COYURI_S      0b0000000000000000000000000000000000000000000000000000000000000001
#define AI_TO_PLAYER_DEF 0b1111111111111111111111111111111111111111111111111111111111111110

#define EMPTY       0b0000000000000000000000000000000000000000000000000000000000000000
#define HU          0b0000000000000000000000000000000000000000000000000000000000000010
#define KYOUSHA     0b0000000000000000000000000000000000000000000000000000000000000100
#define KEIMA       0b0000000000000000000000000000000000000000000000000000000000001000
#define GIN         0b0000000000000000000000000000000000000000000000000000000000010000
#define KIN         0b0000000000000000000000000000000000000000000000000000000000100000
#define HISHA       0b0000000000000000000000000000000000000000000000000000000001000000
#define KAKU        0b0000000000000000000000000000000000000000000000000000000010000000
#define TOKIN       0b0000000000000000000000000000000000000000000000000000000100000000
#define NARIKYOU    0b0000000000000000000000000000000000000000000000000000001000000000
#define NARIKEI     0b0000000000000000000000000000000000000000000000000000010000000000
#define NARIGIN     0b0000000000000000000000000000000000000000000000000000100000000000
#define RYU         0b0000000000000000000000000000000000000000000000000001000000000000
#define UMA         0b0000000000000000000000000000000000000000000000000010000000000000
#define OU          0b0000000000000000000000000000000000000000000000000100000000000000

#define EN_HU       0b0000000000000000000000000000000000000000000000000000000000000011
#define EN_KYOUSHA  0b0000000000000000000000000000000000000000000000000000000000000101
#define EN_KEIMA    0b0000000000000000000000000000000000000000000000000000000000001001
#define EN_GIN      0b0000000000000000000000000000000000000000000000000000000000010001
#define EN_KIN      0b0000000000000000000000000000000000000000000000000000000000100001
#define EN_HISHA    0b0000000000000000000000000000000000000000000000000000000001000001
#define EN_KAKU     0b0000000000000000000000000000000000000000000000000000000010000001
#define EN_TOKIN    0b0000000000000000000000000000000000000000000000000000000100000001
#define EN_NARIKYOU 0b0000000000000000000000000000000000000000000000000000001000000001
#define EN_NARIKEI  0b0000000000000000000000000000000000000000000000000000010000000001
#define EN_NARIGIN  0b0000000000000000000000000000000000000000000000000000100000000001
#define EN_RYU      0b0000000000000000000000000000000000000000000000000001000000000001
#define EN_UMA      0b0000000000000000000000000000000000000000000000000010000000000001
#define EN_OU       0b0000000000000000000000000000000000000000000000000100000000000001



//XORする
#define _AI_TO_PLAYER_NEGAERI(type) (type & AI_TO_PLAYER_DEF)
#define _PLAYER_TO_AI_NEGAERI(type) (type | AI_COYURI_S)
#define _IS_EMPTY(type) (!type)
#define _IS_NOT_EMPTY(type) (type)
#define _EQUALS(type1, type2) (type1 & type2)
#define _IS_AI_KOMA(type) (type & AI_COYURI_S)
#define _IS_PLAYER_KOMA(type) ( !(type & AI_COYURI_S) )

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
#define _MOCHIGOMA_LIMIT 38

class BANMEN {
	KOMA_TYPE **banmen;
public:
	BANMEN();
	~BANMEN();
	KOMA_TYPE get_type(int x, int y);
	void set_type(int x, int y, KOMA_TYPE type);
	void copy_banmen(BANMEN *original);
	Point find_koma(KOMA_TYPE type);
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
	i64_t evalue;

public:

	u8_t  turn;

	Node(BANMEN *ban, Node *pare, MochiGoma *ai_mochi, MochiGoma *pl_mochi);
	Node(BANMEN *ban, Node *pare, MochiGoma *ai_mochi, MochiGoma *pl_mochi, u8_t turn_arg);
	Node(BANMEN *ban, Node *pare);
	~Node();
	MochiGoma *ai_mochigoma;
	MochiGoma *pl_mochigoma;
	BANMEN *get_banmen();
	std::vector<Node *> *get_children();
	i64_t get_evalue();
	void set_evalue(int value);
	void delete_children();

	static bool compare(Node *a, Node *b)
	{
		return (a->evalue < b->evalue);
	}

};

inline MochiGoma *clone_mochigoma(MochiGoma *source) {
	MochiGoma *uketori = new MochiGoma;
	u8_t size = source->size(), i;
	for (i = 0; i < size; ++i) {
		uketori->push_back(source->at(i));
	}
	return uketori;
}

struct Banmen {

	std::vector<KOMA_TYPE> ai_on_ban;
	std::vector<KOMA_TYPE> pl_on_ban;
	std::vector<KOMA_TYPE> ai_mochigoma;
	std::vector<KOMA_TYPE> pl_mochigoma;

	Banmen() {}
	Banmen(Banmen *ban) {
		u8_t size, i;
		size = ban->ai_on_ban.size();
		for (i = 0; i < size; ++i) {
			ai_on_ban.push_back(ban->ai_on_ban.at(i));
		}

		size = ban->pl_on_ban.size();
		for (i = 0; i < size; ++i) {
			pl_on_ban.push_back(ban->pl_on_ban.at(i));
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
	Node *load_file(const char *file_name) {

		BANMEN *ban = new BANMEN;
		MochiGoma *ai_mochi = new MochiGoma, *pl_mochi = new MochiGoma;

		i64_t i_t_i;
		std::ifstream ifs(file_name);
		if (ifs.fail()) {
			puts("FAILD");
			exit(0);
		}
		std::string str;

		std::getline(ifs, str);
		/*
		*strの中身である、手数は今の所使わないので捨てる
		*/

		for (u8_t y = 0; y < 9; ++y) {
			std::getline(ifs, str);
			std::stringstream ss(str);

			for (u8_t x = 0; x < 9; ++x) {
				ss >> i_t_i;
				ban->set_type(x, y, convert_array[i_t_i]);
			}
		}

		std::getline(ifs, str);
		load_mochi(ai_mochi, str);

		std::getline(ifs, str);
		load_mochi(pl_mochi, str);

		return new Node(ban, nullptr, ai_mochi, pl_mochi, _AI_TURN);
	}
};

class CoyuriIniter {

private:
	FileLoader file_loader;

public:
	void init(const char *file_name, Node **node) {
		*node = file_loader.load_file(file_name);
	}

};


#endif
