#ifndef VALUE_HPP
#define VALUE_HPP

#include <unordered_map>
#include <cstdint>

using KOMA_TYPE = std::uint_fast8_t;

extern std::unordered_map<KOMA_TYPE, KOMA_TYPE> naru_map;
constexpr i64_t _NGST_SEARCH_INIT_SCORE_MAX_VALUE = -10000000;

#endif
