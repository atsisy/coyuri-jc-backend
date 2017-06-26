#include "types.hpp"

KomaGroup::KomaGroup() 
{}

KomaGroup::KomaGroup(u8_t size) 
	: group_member(size)
{}

void KomaGroup::move(PiP _pip, Point2d8 _gone_point)
{
	u8_t i, size;
	for (i = 0, size = group_member.size(); i < size; ++i) {
		if (this->group_member.at(i) == _pip) {
			this->group_member.at(i) = ((_gone_point << 8) | _pip_get_type(_pip));
			return;
		}
	}
	return;
}

void KomaGroup::erase(PiP _pip) 
{
	u8_t i, size;
	for (i = 0, size = group_member.size(); i < size; ++i) {
		if (this->group_member.at(i) == _pip) {
			this->group_member.at(i) = _KOMA_GROUP_DISABLE_FLAG;
			return;
		}
	}
	return;
}

void KomaGroup::push(PiP _pip)
{
	group_member.push_back(_pip);
}

KomaGroup *KomaGroup::clone()
{
	u8_t i, size;
	KomaGroup *clone_group = new KomaGroup(this->group_member.size());
	for (i = 0, size = group_member.size(); i < size; ++i) {
		if (this->group_member.at(i) != _KOMA_GROUP_DISABLE_FLAG) {
			clone_group->group_member.at(i) = this->group_member.at(i);
		}
	}
	return clone_group;
}