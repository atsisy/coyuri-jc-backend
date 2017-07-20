#include "types.hpp"
#include "prot.hpp"
#include "values.hpp"


extern std::function<std::vector<Point>(BANMEN *, Point)> wcm_function_table[29];

void ai_add_node_from_mochi_expand(Node *node, KOMA_TYPE type)
{
	BANMEN *new_banmen;
	u8_t n;
	std::vector<Point> points;

	node->ai_mochigoma->decrease(type);
	points = tegoma_wcm(node->get_banmen(), Point(-1, -1));
	for (n = 0; n < points.size(); ++n) {
		new_banmen = new BANMEN;
		new_banmen->copy_banmen(node->get_banmen());
		new_banmen->set_type(points.at(n).x, points.at(n).y, type);
		node->get_children().push_back(new Node(new_banmen, node));
	}
	node->ai_mochigoma->increase(type);
}

void pl_add_node_from_mochi_expand(Node *node, KOMA_TYPE type)
{
	BANMEN *new_banmen;
	u8_t n;
	std::vector<Point> points;

	node->pl_mochigoma->decrease(type);
	points = tegoma_wcm(node->get_banmen(), Point(-1, -1));
	for (n = 0; n < points.size(); ++n) {
		new_banmen = new BANMEN;
		new_banmen->copy_banmen(node->get_banmen());
		new_banmen->set_type(points.at(n).x, points.at(n).y, type);
		node->get_children().push_back(new Node(new_banmen, node));
	}
	node->pl_mochigoma->increase(type);
}

/*
*渡された盤面からコンピュータがさせる手をすべてリストアップする関数
*/
void EXPAND(Node *node) {

	/*
	*AIが持ち駒を打つ場合
	*/
	u8_t size, x, y, n;
	KOMA_TYPE koma, may_get_koma;
	BANMEN *new_banmen;
	AIMochiGomaGroup *ai_mochi;
	PLMochiGomaGroup *pl_mochi;
	Point point_regi(0, 0);
	std::vector<Point> points;

	if (node->ai_mochigoma->check_size(EN_HU))
	{
		node->ai_mochigoma->decrease(EN_HU);
		points = ai_nihu_wcm(node->get_banmen());
		for (n = 0, size = points.size(); n < size; ++n) {
			new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());
			new_banmen->set_type(points.at(n).x, points.at(n).y, EN_HU);
			node->get_children().push_back(new Node(new_banmen, node));
		}
		node->ai_mochigoma->increase(EN_HU);
	}
	
	if (node->ai_mochigoma->check_size(EN_KYOUSHA))
	{
		node->ai_mochigoma->decrease(EN_KYOUSHA);
		points = ai_mochi_kyousha_wcm(node->get_banmen());
		for (n = 0, size = points.size(); n < size; ++n) {
			new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());
			new_banmen->set_type(points.at(n).x, points.at(n).y, EN_KYOUSHA);
			node->get_children().push_back(new Node(new_banmen, node));
		}
		node->ai_mochigoma->increase(EN_KYOUSHA);
	}

	if (node->ai_mochigoma->check_size(EN_KEIMA))
	{
		node->ai_mochigoma->decrease(EN_KEIMA);
		points = ai_mochi_keima_wcm(node->get_banmen());
		for (n = 0, size = points.size(); n < size; ++n) {
			new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());
			new_banmen->set_type(points.at(n).x, points.at(n).y, EN_KEIMA);
			node->get_children().push_back(new Node(new_banmen, node));
		}
		node->ai_mochigoma->increase(EN_KEIMA);
	}

	if (node->ai_mochigoma->check_size(EN_GIN)) {
		ai_add_node_from_mochi_expand(node, EN_GIN);
	}
	if (node->ai_mochigoma->check_size(EN_KIN)) {
		ai_add_node_from_mochi_expand(node, EN_KIN);
	}
	if (node->ai_mochigoma->check_size(EN_KAKU)) {
		ai_add_node_from_mochi_expand(node, EN_KAKU);
	}
	if (node->ai_mochigoma->check_size(EN_HISHA)) {
		ai_add_node_from_mochi_expand(node, EN_HISHA);
	}

	for (x = 0; x < 9; ++x) {
		for (y = 0; y < 9; ++y) {
			koma = node->get_banmen()->get_type(x, y);
			if (_IS_AI_KOMA(koma)) {
				points = wcm_function_table[_KOMA_TO_INDEX(koma)](node->get_banmen(), Point(x, y));
				size = points.size();
				for (n = 0; n < size; ++n) {
					point_regi = points.at(n);
					new_banmen = new BANMEN;
					new_banmen->copy_banmen(node->get_banmen());
					ai_mochi = node->ai_mochigoma->clone();
					pl_mochi = node->pl_mochigoma->clone();
					may_get_koma = node->get_banmen()->get_type(point_regi.x, point_regi.y);

					if (_IS_NOT_EMPTY(may_get_koma))
					{
						ai_mochi->increase(_NEGAERI(may_get_koma));
					}

					if (point_regi.y >= 6) {
						/*
						*プレイヤーの陣地まで行ったので、成る処理をしたい
						*/
						new_banmen->set_type(point_regi.x, point_regi.y, naru_map.at(koma));
						new_banmen->set_type(x, y, EMPTY);
						node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));

						/*
						*ならない場合も検討
						*AIは銀、香車、桂馬のみ成る判定を行う
						*/
						if (_EQUALS(koma, EN_GIN) || _EQUALS(koma, EN_KYOUSHA) || _EQUALS(koma, EN_KEIMA)) 
						{
							new_banmen = new BANMEN;
							new_banmen->copy_banmen(node->get_banmen());
							new_banmen->set_type(point_regi.x, point_regi.y, koma);
							new_banmen->set_type(x, y, EMPTY);

							pl_mochi = node->pl_mochigoma->clone();
							ai_mochi = node->ai_mochigoma->clone();
							node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
						}
					}
					else {
						/*
						*成る処理は必要ない
						*/
						new_banmen->set_type(point_regi.x, point_regi.y, koma);
						new_banmen->set_type(x, y, EMPTY);
						node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
					}
				}
			}
		}
	}
}

void AI_EXPAND_ONLY_ON_BOARD(Node *node)
{
	u8_t size, n;
	KOMA_TYPE koma, may_get_koma;
	BANMEN *new_banmen;
	AIMochiGomaGroup *ai_mochi;
	PLMochiGomaGroup *pl_mochi;
	Point point_regi(0, 0);
	std::vector<Point> points;

	for (u8_t x = 0; x < 9; ++x) {
		for (u8_t y = 0; y < 9; ++y) {
			koma = node->get_banmen()->get_type(x, y);
			if (_IS_AI_KOMA(koma)) {
				points = wcm_function_table[_KOMA_TO_INDEX(koma)](node->get_banmen(), Point(x, y));
				size = points.size();
				for (n = 0; n < size; ++n) {
					point_regi = points.at(n);
					new_banmen = new BANMEN;
					new_banmen->copy_banmen(node->get_banmen());
					ai_mochi = node->ai_mochigoma->clone();
					pl_mochi = node->pl_mochigoma->clone();
					may_get_koma = node->get_banmen()->get_type(point_regi.x, point_regi.y);

					if (_IS_NOT_EMPTY(may_get_koma))
					{
						ai_mochi->increase(_NEGAERI(may_get_koma));
					}

					if (point_regi.y >= 6) {
						/*
						*プレイヤーの陣地まで行ったので、成る処理をしたい
						*/
						new_banmen->set_type(point_regi.x, point_regi.y, naru_map.at(koma));
						new_banmen->set_type(x, y, EMPTY);
						node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));

						/*
						*ならない場合も検討
						*/
						if (_EQUALS(koma, EN_GIN) || _EQUALS(koma, EN_KYOUSHA) || _EQUALS(koma, EN_KEIMA))
						{
							pl_mochi = node->pl_mochigoma->clone();
							ai_mochi = node->ai_mochigoma->clone();
							new_banmen = new BANMEN;
							new_banmen->copy_banmen(node->get_banmen());
							new_banmen->set_type(point_regi.x, point_regi.y, koma);
							new_banmen->set_type(x, y, EMPTY);
							node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
						}
					}
					else {
						/*
						*成る処理は必要ない
						*/
						new_banmen->set_type(point_regi.x, point_regi.y, koma);
						new_banmen->set_type(x, y, EMPTY);
						node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
					}
				}
			}
		}
	}
}

void AI_EXPAND_ONLY_MOCHIGOMA(Node *node)
{
	std::vector<Point> points;
	BANMEN *new_banmen;
	u8_t n;

	if (node->ai_mochigoma->check_size(EN_HU))
	{
		node->ai_mochigoma->decrease(EN_HU);
		points = ai_nihu_wcm(node->get_banmen());
		for (n = 0; n < points.size(); ++n) {
			new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());
			new_banmen->set_type(points.at(n).x, points.at(n).y, EN_HU);
			node->get_children().push_back(new Node(new_banmen, node));
		}
		node->ai_mochigoma->increase(EN_HU);
	}

	if (node->ai_mochigoma->check_size(EN_KYOUSHA))
	{
		node->ai_mochigoma->decrease(EN_KYOUSHA);
		points = ai_mochi_kyousha_wcm(node->get_banmen());
		for (n = 0; n < points.size(); ++n) {
			new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());
			new_banmen->set_type(points.at(n).x, points.at(n).y, EN_KYOUSHA);
			node->get_children().push_back(new Node(new_banmen, node));
		}
		node->ai_mochigoma->increase(EN_KYOUSHA);
	}

	if (node->ai_mochigoma->check_size(EN_KEIMA))
	{
		node->ai_mochigoma->decrease(EN_KEIMA);
		points = ai_mochi_keima_wcm(node->get_banmen());
		for (n = 0; n < points.size(); ++n) {
			new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());
			new_banmen->set_type(points.at(n).x, points.at(n).y, EN_KEIMA);
			node->get_children().push_back(new Node(new_banmen, node));
		}
		node->ai_mochigoma->increase(EN_KEIMA);
	}

	if (node->ai_mochigoma->check_size(EN_GIN)) {
		ai_add_node_from_mochi_expand(node, EN_GIN);
	}
	if (node->ai_mochigoma->check_size(EN_KIN)) {
		ai_add_node_from_mochi_expand(node, EN_KIN);
	}
	if (node->ai_mochigoma->check_size(EN_KAKU)) {
		ai_add_node_from_mochi_expand(node, EN_KAKU);
	}
	if (node->ai_mochigoma->check_size(EN_HISHA)) {
		ai_add_node_from_mochi_expand(node, EN_HISHA);
	}
}

/*
*渡された盤面からプレイヤーがさせる手をすべてリストアップする関数
*/
void PLAYER_EXPAND(Node *node) {
	/*
	*プレイヤーが持ち駒を打つ場合
	*/
	u8_t x, y, size, n;
	KOMA_TYPE koma, may_get_koma;
	std::vector<Point> points;
	BANMEN *new_banmen;
	AIMochiGomaGroup *ai_mochi;
	PLMochiGomaGroup *pl_mochi;
	Point point_regi(0, 0);

	if (node->pl_mochigoma->check_size(HU))
	{
		node->pl_mochigoma->decrease(HU);
		points = pl_nihu_wcm(node->get_banmen());
		for (n = 0, size = points.size(); n < size; ++n) {
			new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());
			new_banmen->set_type(points.at(n).x, points.at(n).y, HU);
			node->get_children().push_back(new Node(new_banmen, node));
		}
		node->pl_mochigoma->increase(HU);
	}

	if (node->pl_mochigoma->check_size(KYOUSHA))
	{
		node->pl_mochigoma->decrease(KYOUSHA);
		points = pl_mochi_kyousha_wcm(node->get_banmen());
		for (n = 0, size = points.size(); n < size; ++n) {
			new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());
			new_banmen->set_type(points.at(n).x, points.at(n).y, KYOUSHA);
			node->get_children().push_back(new Node(new_banmen, node));
		}
		node->pl_mochigoma->increase(KYOUSHA);
	}

	if (node->pl_mochigoma->check_size(KEIMA))
	{
		node->pl_mochigoma->decrease(KEIMA);
		points = pl_mochi_keima_wcm(node->get_banmen());
		for (n = 0, size = points.size(); n < size; ++n) {
			new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());
			new_banmen->set_type(points.at(n).x, points.at(n).y, KEIMA);
			node->get_children().push_back(new Node(new_banmen, node));
		}
		node->pl_mochigoma->increase(KEIMA);
	}

	if (node->pl_mochigoma->check_size(GIN)) {
		pl_add_node_from_mochi_expand(node, GIN);
	}
	if (node->pl_mochigoma->check_size(KIN)) {
		pl_add_node_from_mochi_expand(node, KIN);
	}
	if (node->pl_mochigoma->check_size(KAKU)) {
		pl_add_node_from_mochi_expand(node, KAKU);
	}
	if (node->pl_mochigoma->check_size(HISHA)) {
		pl_add_node_from_mochi_expand(node, HISHA);
	}

	for (x = 0; x < 9; ++x) {
		for (y = 0; y < 9; ++y) {
			koma = node->get_banmen()->get_type(x, y);
			if (_IS_PLAYER_KOMA(koma)) {
				points = wcm_function_table[_KOMA_TO_INDEX(koma)](node->get_banmen(), Point(x, y));
				size = points.size();
				for (n = 0; n < size; ++n) {
					point_regi = points.at(n);

					pl_mochi = node->pl_mochigoma->clone();
					ai_mochi = node->ai_mochigoma->clone();
					may_get_koma = node->get_banmen()->get_type(point_regi.x, point_regi.y);

					if (_IS_NOT_EMPTY(may_get_koma))
					{
						if (may_get_koma == EN_OU)
						{
							delete pl_mochi;
							continue;
						}
						else {
							pl_mochi->increase(_NEGAERI(may_get_koma));
						}
					}

					new_banmen = new BANMEN;
					new_banmen->copy_banmen(node->get_banmen());

					if (point_regi.y <= 2) {
						/*
						*なる必要がある
						*/
						new_banmen->set_type(point_regi.x, point_regi.y, naru_map.at(koma));
						new_banmen->set_type(x, y, EMPTY);
						node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));

						/*
						*ならない場合も検討
						*/
						if (_EQUALS(koma, GIN) || _EQUALS(koma, KYOUSHA) || _EQUALS(koma, KEIMA))
						{
							pl_mochi = node->pl_mochigoma->clone();
							ai_mochi = node->ai_mochigoma->clone();
							new_banmen = new BANMEN;
							new_banmen->copy_banmen(node->get_banmen());
							new_banmen->set_type(point_regi.x, point_regi.y, koma);
							new_banmen->set_type(x, y, EMPTY);
							node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
						}
					}
					else {
						/*
						*なる必要は無い
						*/
						new_banmen->set_type(point_regi.x, points.at(n).y, koma);
						new_banmen->set_type(x, y, EMPTY);
						node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
					}
				}
			}
		}
	}
}

void PLAYER_EXPAND_ONLY_ON_BOARD(Node *node)
{
	u8_t x, y, size, n;
	KOMA_TYPE koma, may_get_koma;
	std::vector<Point> points;
	BANMEN *new_banmen;
	AIMochiGomaGroup *ai_mochi;
	PLMochiGomaGroup *pl_mochi;
	Point point_regi(0, 0);

	for (x = 0; x < 9; ++x) {
		for (y = 0; y < 9; ++y) {
			koma = node->get_banmen()->get_type(x, y);
			if (_IS_PLAYER_KOMA(koma)) {
				points = wcm_function_table[_KOMA_TO_INDEX(koma)](node->get_banmen(), Point(x, y));
				size = points.size();
				for (n = 0; n < size; ++n) {
					point_regi = points.at(n);

					pl_mochi = node->pl_mochigoma->clone();
					ai_mochi = node->ai_mochigoma->clone();
					may_get_koma = node->get_banmen()->get_type(point_regi.x, point_regi.y);

					if (_IS_NOT_EMPTY(may_get_koma))
					{
						if (may_get_koma == EN_OU)
						{
							delete pl_mochi;
							continue;
						}
						else {
							pl_mochi->increase(_NEGAERI(may_get_koma));
						}
					}

					new_banmen = new BANMEN;
					new_banmen->copy_banmen(node->get_banmen());

					if (point_regi.y <= 2) {
						/*
						*なる必要がある
						*/
						new_banmen->set_type(point_regi.x, point_regi.y, naru_map.at(koma));
						new_banmen->set_type(x, y, EMPTY);
						node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));

						/*
						*ならない場合も検討
						*/
						if (_EQUALS(koma, GIN) || _EQUALS(koma, KYOUSHA) || _EQUALS(koma, KEIMA))
						{
							new_banmen = new BANMEN;
							new_banmen->copy_banmen(node->get_banmen());
							new_banmen->set_type(point_regi.x, point_regi.y, koma);
							new_banmen->set_type(x, y, EMPTY);
							pl_mochi = node->pl_mochigoma->clone();
							ai_mochi = node->ai_mochigoma->clone();
							node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
						}
					}
					else {
						/*
						*なる必要は無い
						*/
						new_banmen->set_type(point_regi.x, points.at(n).y, koma);
						new_banmen->set_type(x, y, EMPTY);
						node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
					}
				}
			}
		}
	}
}

void PLAYER_EXPAND_ONLY_MOCHIGOMA(Node *node)
{
	std::vector<Point> points;
	BANMEN *new_banmen;
	u8_t n, size;

	if (node->pl_mochigoma->check_size(HU))
	{
		node->pl_mochigoma->decrease(HU);
		points = pl_nihu_wcm(node->get_banmen());
		for (n = 0, size = points.size(); n < size; ++n) {
			new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());
			new_banmen->set_type(points.at(n).x, points.at(n).y, HU);
			node->get_children().push_back(new Node(new_banmen, node));
		}
		node->pl_mochigoma->increase(HU);
	}

	if (node->pl_mochigoma->check_size(KYOUSHA))
	{
		node->pl_mochigoma->decrease(KYOUSHA);
		points = pl_mochi_kyousha_wcm(node->get_banmen());
		for (n = 0, size = points.size(); n < size; ++n) {
			new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());
			new_banmen->set_type(points.at(n).x, points.at(n).y, KYOUSHA);
			node->get_children().push_back(new Node(new_banmen, node));
		}
		node->pl_mochigoma->increase(KYOUSHA);
	}

	if (node->pl_mochigoma->check_size(KEIMA))
	{
		node->pl_mochigoma->decrease(KEIMA);
		points = pl_mochi_keima_wcm(node->get_banmen());
		for (n = 0, size = points.size(); n < size; ++n) {
			new_banmen = new BANMEN;
			new_banmen->copy_banmen(node->get_banmen());
			new_banmen->set_type(points.at(n).x, points.at(n).y, KEIMA);
			node->get_children().push_back(new Node(new_banmen, node));
		}
		node->pl_mochigoma->increase(KEIMA);
	}

	if (node->pl_mochigoma->check_size(GIN)) {
		pl_add_node_from_mochi_expand(node, GIN);
	}
	if (node->pl_mochigoma->check_size(KIN)) {
		pl_add_node_from_mochi_expand(node, KIN);
	}
	if (node->pl_mochigoma->check_size(KAKU)) {
		pl_add_node_from_mochi_expand(node, KAKU);
	}
	if (node->pl_mochigoma->check_size(HISHA)) {
		pl_add_node_from_mochi_expand(node, HISHA);
	}
}


void ai_conflicting_expand(Node *node) {

	/*
	*AIが持ち駒を打つ場合
	*/
	u8_t size, x, y, n;
	KOMA_TYPE koma, may_get_koma;
	BANMEN *new_banmen;
	AIMochiGomaGroup *ai_mochi;
	PLMochiGomaGroup *pl_mochi;
	Point point_regi(0, 0);
	std::vector<Point> points;

	for (x = 0; x < 9; ++x) {
		for (y = 0; y < 9; ++y) {
			koma = node->get_banmen()->get_type(x, y);
			if (_IS_AI_KOMA(koma)) {
				points = wcm_function_table[_KOMA_TO_INDEX(koma)](node->get_banmen(), Point(x, y));
				for (n = 0, size = points.size(); n < size; ++n) {
					point_regi = points.at(n);
					if (_IS_PLAYER_KOMA(may_get_koma = node->get_banmen()->get_type(point_regi.x, point_regi.y)))
					{
						new_banmen = new BANMEN;
						new_banmen->copy_banmen(node->get_banmen());
						ai_mochi = node->ai_mochigoma->clone();
						pl_mochi = node->pl_mochigoma->clone();
						ai_mochi->increase(_NEGAERI(may_get_koma));

						if (point_regi.y >= 6) {
							/*
							*プレイヤーの陣地まで行ったので、成る処理をしたい
							*/
							new_banmen->set_type(point_regi.x, point_regi.y, naru_map.at(koma));
							new_banmen->set_type(x, y, EMPTY);
							node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));

						}
						else {
							/*
							*成る処理は必要ない
							*/
							new_banmen->set_type(point_regi.x, point_regi.y, koma);
							new_banmen->set_type(x, y, EMPTY);
							node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
						}

					}
				}
			}
		}
	}
}

void pl_conflicting_expand(Node *node) {

	/*
	*AIが持ち駒を打つ場合
	*/
	u8_t size, x, y, n;
	KOMA_TYPE koma, may_get_koma;
	BANMEN *new_banmen;
	AIMochiGomaGroup *ai_mochi;
	PLMochiGomaGroup *pl_mochi;
	Point point_regi(0, 0);
	std::vector<Point> points;
	/*
	if (node->ai_mochigoma->check_size(EN_HU))
	{
	node->ai_mochigoma->decrease(EN_HU);
	points = ai_nihu_wcm(node->get_banmen());
	for (n = 0, size = points.size(); n < size; ++n) {
	new_banmen = new BANMEN;
	new_banmen->copy_banmen(node->get_banmen());
	new_banmen->set_type(points.at(n).x, points.at(n).y, EN_HU);
	node->get_children().push_back(new Node(new_banmen, node));
	}
	node->ai_mochigoma->increase(EN_HU);
	}

	if (node->ai_mochigoma->check_size(EN_KYOUSHA))
	{
	node->ai_mochigoma->decrease(EN_KYOUSHA);
	points = ai_mochi_kyousha_wcm(node->get_banmen());
	for (n = 0, size = points.size(); n < size; ++n) {
	new_banmen = new BANMEN;
	new_banmen->copy_banmen(node->get_banmen());
	new_banmen->set_type(points.at(n).x, points.at(n).y, EN_KYOUSHA);
	node->get_children().push_back(new Node(new_banmen, node));
	}
	node->ai_mochigoma->increase(EN_KYOUSHA);
	}

	if (node->ai_mochigoma->check_size(EN_KEIMA))
	{
	node->ai_mochigoma->decrease(EN_KEIMA);
	points = ai_mochi_keima_wcm(node->get_banmen());
	for (n = 0, size = points.size(); n < size; ++n) {
	new_banmen = new BANMEN;
	new_banmen->copy_banmen(node->get_banmen());
	new_banmen->set_type(points.at(n).x, points.at(n).y, EN_KEIMA);
	node->get_children().push_back(new Node(new_banmen, node));
	}
	node->ai_mochigoma->increase(EN_KEIMA);
	}

	if (node->ai_mochigoma->check_size(EN_GIN)) {
	ai_add_node_from_mochi_expand(node, EN_GIN);
	}
	if (node->ai_mochigoma->check_size(EN_KIN)) {
	ai_add_node_from_mochi_expand(node, EN_KIN);
	}
	if (node->ai_mochigoma->check_size(EN_KAKU)) {
	ai_add_node_from_mochi_expand(node, EN_KAKU);
	}
	if (node->ai_mochigoma->check_size(EN_HISHA)) {
	ai_add_node_from_mochi_expand(node, EN_HISHA);
	}
	*/


	for (x = 0; x < 9; ++x) {
		for (y = 0; y < 9; ++y) {
			koma = node->get_banmen()->get_type(x, y);
			if (_IS_PLAYER_KOMA(koma)) {
				points = wcm_function_table[_KOMA_TO_INDEX(koma)](node->get_banmen(), Point(x, y));
				for (n = 0, size = points.size(); n < size; ++n) {
					point_regi = points.at(n);
					if (_IS_AI_KOMA(may_get_koma = node->get_banmen()->get_type(point_regi.x, point_regi.y)))
					{
						new_banmen = new BANMEN;
						new_banmen->copy_banmen(node->get_banmen());
						ai_mochi = node->ai_mochigoma->clone();
						pl_mochi = node->pl_mochigoma->clone();
						pl_mochi->increase(_NEGAERI(may_get_koma));

						if (point_regi.y >= 6) {
							/*
							*プレイヤーの陣地まで行ったので、成る処理をしたい
							*/
							new_banmen->set_type(point_regi.x, point_regi.y, naru_map.at(koma));
							new_banmen->set_type(x, y, EMPTY);
							node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));

							/*
							*ならない場合も検討
							*/
							new_banmen = new BANMEN;
							new_banmen->copy_banmen(node->get_banmen());
							new_banmen->set_type(point_regi.x, point_regi.y, koma);
							new_banmen->set_type(x, y, EMPTY);

							pl_mochi = node->pl_mochigoma->clone();
							ai_mochi = node->ai_mochigoma->clone();
							node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
						}
						else {
							/*
							*成る処理は必要ない
							*/
							new_banmen->set_type(point_regi.x, point_regi.y, koma);
							new_banmen->set_type(x, y, EMPTY);
							node->get_children().push_back(new Node(new_banmen, node, ai_mochi, pl_mochi));
						}

					}
				}
			}
		}
	}
}