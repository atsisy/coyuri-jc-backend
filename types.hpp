﻿#ifndef _TYPES_HPP
#define _TYPES_HPP

#include <string>
#include <vector>
#include <deque>
#include <cstdint>

using u8_t = std::uint_fast8_t;
using u16_t = std::uint_fast16_t;
using u32_t = std::uint_fast32_t;
using u64_t = std::uint_fast64_t;

using i8_t = std::int_fast8_t;
using i16_t = std::int_fast16_t;
using i32_t = std::int_fast32_t;
using i64_t = std::int_fast64_t;

using KOMA_TYPE = u8_t;

#define LEGACY
//#define MODERN

#ifndef MODERN

#define EMPTY 0
#define TARGET 1
#define HU 2
#define KYOUSHA 3
#define KEIMA 4
#define GIN 5
#define KIN 6
#define HISHA 7
#define KAKU 8
#define TOKIN 9
#define NARIKYOU 10
#define NARIKEI 11
#define NARIGIN 12
#define RYU 13
#define UMA 14
#define OU 15
#define EN_HU 16
#define EN_KYOUSHA 17
#define EN_KEIMA 18
#define EN_GIN 19
#define EN_KIN 20
#define EN_HISHA 21
#define EN_KAKU 22
#define EN_TOKIN 23
#define EN_NARIKYOU 24
#define EN_NARIKEI 25
#define EN_NARIGIN 26
#define EN_RYU 27
#define EN_UMA 28
#define EN_OU 29
#define TEGOMA 30

#endif

#ifndef LEGACY

/*
* ビット演算による駒の判別のためのID
*
* LSBはプレイヤーの駒か、見方の細かを判別するためのビット。PLAYER_SとAI_COYURI_Sを使ってアンド演算等で判定
* 
* 
*
*/

#define PLAYER_S    0b0000000000000000000000000000000000000000000000000000000000000000
#define AI_COYURI_S 0b0000000000000000000000000000000000000000000000000000000000000001

#define EMPTY    0b0000000000000000000000000000000000000000000000000000000000000000
#define HU       0b0000000000000000000000000000000000000000000000000000000000000010
#define KYOUSHA  0b0000000000000000000000000000000000000000000000000000000000000100
#define KEIMA    0b0000000000000000000000000000000000000000000000000000000000001000
#define GIN      0b0000000000000000000000000000000000000000000000000000000000010000
#define KIN      0b0000000000000000000000000000000000000000000000000000000000100000
#define HISHA    0b0000000000000000000000000000000000000000000000000000000001000000
#define KAKU     0b0000000000000000000000000000000000000000000000000000000010000000
#define TOKIN    0b0000000000000000000000000000000000000000000000000000000100000000
#define NARIKYOU 0b0000000000000000000000000000000000000000000000000000001000000000
#define NARIKEI  0b0000000000000000000000000000000000000000000000000000010000000000
#define NARIGIN  0b0000000000000000000000000000000000000000000000000000100000000000
#define RYU      0b0000000000000000000000000000000000000000000000000001000000000000
#define UMA      0b0000000000000000000000000000000000000000000000000010000000000000
#define OU       0b0000000000000000000000000000000000000000000000000100000000000000

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
#define _NEGAERI_MACRO(type) (type ^ AI_COYURI_S)


typedef struct {
	u8_t x : 2;
	u8_t y : 2;
} Point;

#endif


using MochiGoma = std::deque<int>;


#define _D


class Point {
	/*
	*座標の位置を保持する変数
	*/
	int X, Y;
public:
	/*
	*コンストラクタ
	*/
	Point(int x, int y);
	Point();
	/*
	*getter/setter
	*/
	int get_x();
	int get_y();
	void set_x(int x);
	void set_y(int y);
};

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

class Node {

	BANMEN *banmen;
	Node *parent;
	std::vector<Node *> children;
	int evalue;

public:
	MochiGoma *ai_mochigoma;
	MochiGoma *pl_mochigoma;
	~Node();
	Node(BANMEN *ban, Node *pare, MochiGoma *ai_mochi, MochiGoma *pl_mochi);
	Node(BANMEN *ban, Node *pare);
	Node(BANMEN *ban);			//root作成用
	BANMEN *get_banmen();
	std::vector<Node *> *get_children();
	int get_evalue();
	void set_evalue(int value);

};

inline MochiGoma *clone_mochigoma(MochiGoma *source) {
	MochiGoma *uketori = new MochiGoma;
	u8_t size = source->size(), i;
	for (i = 0; i < size; ++i) {
		uketori->push_back(source->at(i));
	}
	return uketori;
}

#endif
