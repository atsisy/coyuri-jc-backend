#ifndef VALUE_HPP
#define VALUE_HPP

#include <vector>
#include <functional>
#include "types.hpp"

extern std::vector<Point>(*wcm_ftable[])(KOMA_TYPE **ban, Point point);
extern KOMA_TYPE(*naru_ftable[])();
extern Point TARGET_KOMA;
extern std::vector<KOMA_TYPE> AI_TEGOMA;
extern std::vector<KOMA_TYPE> PLAYER_TEGOMA;
extern Tegoma *player_tegomas[6][6];
extern Tegoma *ai_tegomas[6][6];
extern KOMA_TYPE UTSU;
extern Point UTSU_KOMA;
extern bool player_finish_flag;
extern bool ai_finish_flag;

#endif
