#ifndef VALUE_HPP
#define VALUE_HPP

#include <vector>
#include "types.hpp"

extern std::vector<Point>(*wcm_ftable[])(KOMA_TYPE **ban, Point point);
extern KOMA_TYPE(*naru_ftable[])();
extern bool player_finish_flag;
extern bool ai_finish_flag;

#endif
