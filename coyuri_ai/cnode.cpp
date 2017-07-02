#include "types.hpp"
#include "coutil.hpp"


Node::~Node() {
	delete banmen;
	ai_mochigoma->clear();
	pl_mochigoma->clear();
	delete ai_mochigoma;
	delete pl_mochigoma;
}

Point sub_nn(KOMA_TYPE **ban, KOMA_TYPE type, Point base) {

	u8_t x, y;

	x = base.x;
	y = base.y;

	if (_EQUALS(ban[x][y], type))
	{
		return Point(x, y);
	}
	--x;
	if (_point_xy_error_check(x, y) && _EQUALS(ban[x][y], type))
	{
		return Point(x, y);
	}
	x += 2;
	if (_point_xy_error_check(x, y) && _EQUALS(ban[x][y], type))
	{
		return Point(x, y);
	}

	--y;
	if (_point_xy_error_check(x, y) && _EQUALS(ban[x][y], type))
	{
		return Point(x, y);
	}
	--x;
	if (_point_xy_error_check(x, y) && _EQUALS(ban[x][y], type))
	{
		return Point(x, y);
	}
	--x;
	if (_point_xy_error_check(x, y) && _EQUALS(ban[x][y], type))
	{
		return Point(x, y);
	}

	y += 2;
	x += 2;
	if (_point_xy_error_check(x, y) && _EQUALS(ban[x][y], type))
	{
		return Point(x, y);
	}
	--x;
	if (_point_xy_error_check(x, y) && _EQUALS(ban[x][y], type))
	{
		return Point(x, y);
	}
	--x;
	if (_point_xy_error_check(x, y) && _EQUALS(ban[x][y], type))
	{
		return Point(x, y);
	}

	return Point(0, 0);

}

Node::Node(Node *pare, Te te)
{
	u8_t size, i;
	KOMA_TYPE regi_koma;
	banmen = pare->banmen;
	parent = pare;

	this->turn = _NEXT_TURN(pare->turn);

	ai_mochigoma = new MochiGoma;
	pl_mochigoma = new MochiGoma;

	size = pare->ai_mochigoma->size();
	for (i = 0; i < size; ++i) {
		ai_mochigoma->push_back(pare->ai_mochigoma->at(i));
	}

	size = pare->pl_mochigoma->size();
	for (i = 0; i < size; ++i) {
		pl_mochigoma->push_back(pare->pl_mochigoma->at(i));
	}

	if (te.from_x != 255)
	{
		if (banmen->get_type(te.from_x, te.from_y) != EN_OU)
		{
			/*
			*AIの王は動かしてない
			*/
			ai_ou_point = pare->ai_ou_point;
		}
		else
		{
			/*
			*王を動かした
			*/
			ai_ou_point.x = te.gone_x;
			ai_ou_point.y = te.gone_y;
		}

		if (banmen->get_type(te.from_x, te.from_y) != OU)
		{
			/*
			*PLの王は動かしてない
			*/
			pl_ou_point = pare->pl_ou_point;
		}
		else
		{
			/*
			*王を動かした
			*/
			pl_ou_point.x = te.gone_x;
			pl_ou_point.y = te.gone_y;
		}
	}

	evalue = 0;
	te_queue.push_back(te);
}


Node::Node(Node *pare, MochiGoma *ai_mochi, MochiGoma *pl_mochi, Te te) 
{
	
	this->banmen = pare->banmen;
	this->parent = pare;

	this->ai_mochigoma = ai_mochi;
	this->pl_mochigoma = pl_mochi;

	this->evalue = 0;
	this->turn = _NEXT_TURN(pare->turn);

	if (banmen->get_type(te.from_x, te.from_y) != EN_OU)
	{
		/*
		*AIの王は動かしてない
		*/
		ai_ou_point = pare->ai_ou_point;
	}
	else
	{
		/*
		*王を動かした
		*/
		ai_ou_point.x = te.gone_x;
		ai_ou_point.y = te.gone_y;
	}

	if (banmen->get_type(te.from_x, te.from_y) != OU)
	{
		/*
		*PLの王は動かしてない
		*/
		pl_ou_point = pare->pl_ou_point;
	}
	else
	{
		/*
		*王を動かした
		*/
		pl_ou_point.x = te.gone_x;
		pl_ou_point.y = te.gone_y;
	}

	te_queue.push_back(te);
}

Node::Node(BANMEN *ban, Node *pare, MochiGoma *ai_mochi, MochiGoma *pl_mochi, u8_t turn_arg, Point arg_ai_ou_point, Point arg_pl_ou_point)
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
		clone_mochigoma(this->ai_mochigoma),
		clone_mochigoma(this->pl_mochigoma),
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

std::vector<Node *> & Node::get_children() {
	return children;
}

i64_t Node::get_evalue() {
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

Te::Te(u8_t x, u8_t y, u8_t will_move_x, u8_t will_move_y, KOMA_TYPE type, u8_t nari, u8_t turn)
{
	from_x = x;
	from_y = y;
	gone_x = will_move_x;
	gone_y = will_move_y;

	this->type = type;

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
	type = EMPTY;
}

