#include "types.hpp"


Node::~Node() {
	delete banmen;
	ai_mochigoma->clear();
	pl_mochigoma->clear();
	delete ai_mochigoma;
	delete pl_mochigoma;
}

Point sub_nn(BANMEN *ban, KOMA_TYPE type, Point base) {

	u8_t x, y;

	x = base.x;
	y = base.y;

	if (_EQUALS(ban->get_type(x, y), EN_OU))
	{
		return point(x, y);
	}
	--x;
	if (_point_xy_error_check(x, y) && _EQUALS(ban->get_type(x, y), EN_OU))
	{
		return point(x, y);
	}
	x += 2;
	if (_point_xy_error_check(x, y) && _EQUALS(ban->get_type(x, y), EN_OU))
	{
		return point(x, y);
	}

	--y;
	if (_point_xy_error_check(x, y) && _EQUALS(ban->get_type(x, y), EN_OU))
	{
		return point(x, y);
	}
	--x;
	if (_point_xy_error_check(x, y) && _EQUALS(ban->get_type(x, y), EN_OU))
	{
		return point(x, y);
	}
	--x;
	if (_point_xy_error_check(x, y) && _EQUALS(ban->get_type(x, y), EN_OU))
	{
		return point(x, y);
	}

	y += 2;
	x += 2;
	if (_point_xy_error_check(x, y) && _EQUALS(ban->get_type(x, y), EN_OU))
	{
		return point(x, y);
	}
	--x;
	if (_point_xy_error_check(x, y) && _EQUALS(ban->get_type(x, y), EN_OU))
	{
		return point(x, y);
	}
	--x;
	if (_point_xy_error_check(x, y) && _EQUALS(ban->get_type(x, y), EN_OU))
	{
		return point(x, y);
	}

}

Node::Node(BANMEN *ban, Node *pare) {
	u8_t size, i;
	banmen = ban;
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

	this->ai_ou_point = sub_nn(ban, EN_OU, pare->ai_ou_point);
	this->pl_ou_point = sub_nn(ban, OU, pare->pl_ou_point);

	evalue = 0;
}

Node::Node(BANMEN *ban, Node *pare, MochiGoma *ai_mochi, MochiGoma *pl_mochi) {
	
	this->banmen = ban;
	this->parent = pare;

	this->ai_mochigoma = ai_mochi;
	this->pl_mochigoma = pl_mochi;


	this->ai_ou_point = sub_nn(ban, EN_OU, pare->ai_ou_point);
	this->pl_ou_point = sub_nn(ban, OU, pare->pl_ou_point);

	this->evalue = 0;
	this->turn = _NEXT_TURN(pare->turn);
}

Node::Node(BANMEN *ban, Node *pare, MochiGoma *ai_mochi, MochiGoma *pl_mochi, u8_t turn_arg, Point arg_ai_ou_point, Point arg_pl_ou_point) {
	this->banmen = ban;
	this->parent = pare;

	this->ai_mochigoma = ai_mochi;
	this->pl_mochigoma = pl_mochi;

	this->evalue = 0;
	this->turn = turn_arg;

	this->ai_ou_point = arg_ai_ou_point;
	this->pl_ou_point = arg_pl_ou_point;
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

Te::Te(u8_t x, u8_t y, KOMA_TYPE type) {
	this->point.x = x;
	this->point.y = y;
	this->type = type;
}