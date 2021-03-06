#include "types.hpp"
#include "coutil.hpp"
#include <algorithm>

u8_t ctoi(char ch) {
	return ('0' <= ch && ch <= '9') ? ch - '0' : 0;
}

Node::~Node() {
	delete banmen;
	delete ai_mochigoma;
	delete pl_mochigoma;
}

Point sub_nn(BANMEN *ban, KOMA_TYPE type, Point base) {

	u8_t x, y;

	x = base.x;
	y = base.y;

	if (_EQUALS(ban->get_type(x, y), type))
	{
		return Point(x, y);
	}
	--x;
	if (_point_xy_error_check(x, y) && _EQUALS(ban->get_type(x, y), type))
	{
		return Point(x, y);
	}
	x += 2;
	if (_point_xy_error_check(x, y) && _EQUALS(ban->get_type(x, y), type))
	{
		return Point(x, y);
	}

	--y;
	if (_point_xy_error_check(x, y) && _EQUALS(ban->get_type(x, y), type))
	{
		return Point(x, y);
	}
	--x;
	if (_point_xy_error_check(x, y) && _EQUALS(ban->get_type(x, y), type))
	{
		return Point(x, y);
	}
	--x;
	if (_point_xy_error_check(x, y) && _EQUALS(ban->get_type(x, y), type))
	{
		return Point(x, y);
	}

	y += 2;
	x += 2;
	if (_point_xy_error_check(x, y) && _EQUALS(ban->get_type(x, y), type))
	{
		return Point(x, y);
	}
	--x;
	if (_point_xy_error_check(x, y) && _EQUALS(ban->get_type(x, y), type))
	{
		return Point(x, y);
	}
	--x;
	if (_point_xy_error_check(x, y) && _EQUALS(ban->get_type(x, y), type))
	{
		return Point(x, y);
	}

	return Point(0, 0);

}

Node::Node(BANMEN *ban, Node *pare) 
	: ai_ou_point(sub_nn(ban, EN_OU, pare->ai_ou_point)), pl_ou_point(sub_nn(ban, OU, pare->pl_ou_point))
{
	u8_t size, i;
	banmen = ban;
	parent = pare;

	this->turn = _NEXT_TURN(pare->turn);

	ai_mochigoma = pare->ai_mochigoma->clone();
	pl_mochigoma = pare->pl_mochigoma->clone();

	evalue = 0;
}

Node::Node(BANMEN *ban, Node *pare, AIMochiGomaGroup *ai_mochi, PLMochiGomaGroup *pl_mochi) 
	: ai_ou_point(sub_nn(ban, EN_OU, pare->ai_ou_point)), pl_ou_point(sub_nn(ban, OU, pare->pl_ou_point))
{
	
	this->banmen = ban;
	this->parent = pare;

	this->ai_mochigoma = ai_mochi;
	this->pl_mochigoma = pl_mochi;

	this->evalue = 0;
	this->turn = _NEXT_TURN(pare->turn);
}

Node::Node(BANMEN *ban, Node *pare, AIMochiGomaGroup *ai_mochi, PLMochiGomaGroup *pl_mochi, u8_t turn_arg, Point arg_ai_ou_point, Point arg_pl_ou_point)
	: ai_ou_point(arg_ai_ou_point), pl_ou_point(arg_pl_ou_point)
{
	this->banmen = ban;
	this->parent = pare;

	this->ai_mochigoma = ai_mochi;
	this->pl_mochigoma = pl_mochi;

	this->evalue = 0;
	this->turn = turn_arg;

}

Node *Node::clone()
{
	BANMEN *clone_ban = new BANMEN;
	clone_ban->copy_banmen(this->banmen);

	return new Node(
		clone_ban,
		this->parent,
		this->ai_mochigoma->clone(),
		this->pl_mochigoma->clone(),
		this->turn,
		this->ai_ou_point,
		this->pl_ou_point);
}

Node *Node::get_parent() {
	return parent;
}

BANMEN *Node::get_banmen() {
	return banmen;
}

BANMEN *Node::get_const_banmen() const
{
	return banmen;
}

std::vector<Node *> & Node::get_children() {
	return children;
}

i64_t Node::get_evalue() const
{
	return evalue;
}

void Node::delete_children() {
	u64_t size = children.size(), i;
	for (i = 0; i < size; ++i)
	{
		delete children.at(i);
		children.at(i) = nullptr;
	}
	children.clear();
}

void Node::set_evalue(int value) {
	evalue = value;
}

Node::Node(Node &&value)
	: ai_ou_point(value.ai_ou_point), pl_ou_point(value.pl_ou_point)
{
	this->banmen = value.banmen;
	this->parent = value.parent;
	this->children = value.children;
	this->ai_mochigoma = value.ai_mochigoma;
	this->pl_mochigoma = value.pl_mochigoma;
	this->turn = value.turn;
	this->evalue = value.evalue;

	value.banmen = nullptr;
	value.parent = nullptr;
	value.ai_mochigoma = nullptr;
	value.pl_mochigoma = nullptr;
}

Te::Te(u8_t x, u8_t y, u8_t will_move_x, u8_t will_move_y, u8_t nari, u8_t turn)
{
	from_x = x;
	from_y = y;
	gone_x = will_move_x;
	gone_y = will_move_y;

	flag = 0;
	flag |= nari;
	flag |= (turn << 1);
}

Te::Te()
{
	from_x = 0;
	from_y = 0;
	gone_x = 0;
	gone_y = 0;
	flag = 0;
}

static std::string dan_to_string(u8_t y_val) {
	switch (y_val)
	{
	case 0:
		return "a";
	case 1:
		return "b";
	case 2:
		return "c";
	case 3:
		return "d";
	case 4:
		return "e";
	case 5:
		return "f";
	case 6:
		return "g";
	case 7:
		return "h";
	case 8:
		return "i";
	default:
		break;
	}
	return std::string();
}

static u8_t string_to_dan(char ch) {
	switch (ch)
	{
	case 'a':
		return 0;
	case 'b':
		return 1;
	case 'c':
		return 2;
	case 'd':
		return 3;
	case 'e':
		return 4;
	case 'f':
		return 5;
	case 'g':
		return 6;
	case 'h':
		return 7;
	case 'i':
		return 8;
	default:
		break;
	}
	return 0;
}

std::string Te::to_string() {
	std::string result;
	
	result.append(std::to_string(9 - this->from_x));
	result.append(dan_to_string(this->from_y));

	result.append(std::to_string(9 - this->gone_x));
	result.append(dan_to_string(this->gone_y));

	return result;

}


Te::Te(std::string src)
{
	from_x = ctoi(src.c_str()[0]);
	from_y = ctoi(string_to_dan(src.c_str()[1]));
	gone_x = ctoi(src.c_str()[2]);
	gone_y = ctoi(string_to_dan(src.c_str()[3]));

}

void exec_te(Node *node, Te te)
{
	KOMA_TYPE move_koma, may_get_koma;
	move_koma = node->get_banmen()->get_type(te.from_x, te.from_y);
	node->get_banmen()->set_type(te.from_x, te.from_y, EMPTY);
	if (_IS_AI_KOMA(move_koma))
	{
		if (_IS_PLAYER_KOMA(may_get_koma = node->get_banmen()->get_type(te.from_x, te.from_y)))
		{
			node->ai_mochigoma->increase(_NEGAERI(may_get_koma));
		}
	}
	else if (_IS_PLAYER_KOMA(move_koma))
	{
		if (_IS_AI_KOMA(may_get_koma = node->get_banmen()->get_type(te.from_x, te.from_y)))
		{
			node->pl_mochigoma->increase(_NEGAERI(may_get_koma));
		}
	}
}