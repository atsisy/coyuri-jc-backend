#ifndef PROT_HPP
#define PROT_HPP

#include "types.hpp"

std::vector<Point> null_wcm(const BANMEN * const ban, Point p);
std::vector<Point> pl_hu_wcm(const BANMEN * const ban, Point point);
std::vector<Point> pl_kyousha_wcm(const BANMEN * const ban, Point point);
std::vector<Point> pl_keima_wcm(const BANMEN * const ban, Point p);
std::vector<Point> pl_gin_wcm(const BANMEN * const ban, Point p);
std::vector<Point> pl_kin_wcm(const BANMEN * const ban, Point p);
std::vector<Point> pl_hisha_wcm(const BANMEN * const ban, Point p);
std::vector<Point> pl_kaku_wcm(const BANMEN * const ban, Point p);
std::vector<Point> pl_ryu_wcm(const BANMEN * const ban, Point p);
std::vector<Point> pl_uma_wcm(const BANMEN * const ban, Point p);
std::vector<Point> pl_ou_wcm(const BANMEN * const ban, Point p);
std::vector<Point> ai_hu_wcm(const BANMEN * const ban, Point point);
std::vector<Point> ai_kyousha_wcm(const BANMEN * const ban, Point point);
std::vector<Point> ai_keima_wcm(const BANMEN * const ban, Point p);
std::vector<Point> ai_gin_wcm(const BANMEN * const ban, Point p);
std::vector<Point> ai_kin_wcm(const BANMEN * const ban, Point p);
std::vector<Point> ai_hisha_wcm(const BANMEN * const ban, Point p);
std::vector<Point> ai_kaku_wcm(const BANMEN * const ban, Point p);
std::vector<Point> ai_ou_wcm(const BANMEN * const ban, Point p);
std::vector<Point> ai_ryu_wcm(const BANMEN * const ban, Point p);
std::vector<Point> ai_uma_wcm(const BANMEN * const ban, Point p);
std::vector<Point> tegoma_wcm(BANMEN *main_ban, Point p);
std::vector<Point> ai_mochi_keima_wcm(BANMEN *main_ban);
std::vector<Point> ai_mochi_kyousha_wcm(BANMEN *main_ban);
std::vector<Point> pl_mochi_keima_wcm(BANMEN *main_ban);
std::vector<Point> pl_mochi_kyousha_wcm(BANMEN *main_ban);
i64_t EVAL(const Node * const node);
void PLAYER_EXPAND(Node *node);
void EXPAND(Node *node);
void AI_EXPAND_ONLY_ON_BOARD(Node *node);
void AI_EXPAND_ONLY_MOCHIGOMA(Node *node);
void PLAYER_EXPAND_ONLY_ON_BOARD(Node *node);
void PLAYER_EXPAND_ONLY_MOCHIGOMA(Node *node);
std::vector<Point> nihu_wcm(BANMEN *main_ban);
std::vector<Point> ai_nihu_wcm(BANMEN *main_ban);
std::vector<Point> pl_nihu_wcm(BANMEN *main_ban);
u8_t ai_targetable(const BANMEN * const ban, u8_t x, u8_t y, std::vector<Point>  *points);
u8_t pl_targetable(const BANMEN * const ban, u8_t x, u8_t y, std::vector<Point>  *points);
i64_t early_eval_function(const Node * const node);
i64_t late_eval_function(const Node * const node);
void ai_conflicting_expand(Node *node);
void pl_conflicting_expand(Node *node);
Point find_ai_ou(const BANMEN * const ban);
Point find_pl_ou(const BANMEN * const ban);

#endif
