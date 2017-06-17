#ifndef VALUE_HPP
#define VALUE_HPP

#include <vector>
#include <map>
#include <functional>
#include "types.hpp"

extern std::map<u64_t, std::function<std::vector<Point>(KOMA_TYPE **, Point)> > function_table;
extern std::map<u64_t, u64_t> naru_map;
extern std::map<KOMA_TYPE, int> koma_to_index;

#endif
