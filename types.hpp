#ifndef _TYPES_HPP
#define _TYPES_HPP

#include <string>
#include <vector>
#include <stdint.h>

typedef uint_fast8_t u8_t;
typedef uint_fast16_t u16_t;
typedef uint_fast32_t u32_t;
typedef uint_fast64_t u64_t;

typedef int_fast8_t  i8_t;
typedef int_fast16_t i16_t;
typedef int_fast32_t i32_t;
typedef int_fast64_t i64_t;

#define _D



enum KOMA_TYPE {
	EMPTY, TARGET,
	HU, KYOUSHA, KEIMA, GIN, KIN, HISHA, KAKU, TOKIN, NARIKYOU, NARIKEI, NARIGIN, RYU, UMA, OU,
	EN_HU, EN_KYOUSHA, EN_KEIMA, EN_GIN, EN_KIN, EN_HISHA, EN_KAKU, EN_TOKIN, EN_NARIKYOU, EN_NARIKEI, EN_NARIGIN, EN_RYU, EN_UMA, EN_OU,
	TEGOMA
};

enum COYURI_EXP {
	DEFAULT, SMILE, UMM
};

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

//class Tegoma {
//	int X, Y;
//	KOMA_TYPE type;
//	int handle(int event);
//
//public:
//	Tegoma(int x, int y, int width, int height, int in_x, int in_y, KOMA_TYPE type);
//	int get_x() { return X; }
//	int get_y() { return Y; }
//	KOMA_TYPE get_type() { return type; }
//	void set_type(KOMA_TYPE arg_type);
//};

#define _MOCHIGOMA_LIMIT 38
typedef struct {
      u8_t pointer;
      KOMA_TYPE tegoma[_MOCHIGOMA_LIMIT];
} MochiGoma;

MochiGoma *create_mochigoma();
#define _free_mochi(mochi) ( free(mochi); )
#define _mochi_push(mochi, type) ( mochi->tegoma[mochi->pointer] = type; ++mochi->pointer; )



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
      MochiGoma *mochi_goma;
	~Node();
	Node(BANMEN *ban, Node *pare);
	BANMEN *get_banmen();
	std::vector<Node *> *get_children();
	int get_evalue();
	void set_evalue(int value);

};

#endif
