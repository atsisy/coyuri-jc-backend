#ifndef PROT_HPP
#define PROT_HPP

#include "types.hpp"

std::vector<Point> null_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> pl_hu_wcm(KOMA_TYPE **ban, Point point);
std::vector<Point> pl_kyousha_wcm(KOMA_TYPE **ban, Point point);
std::vector<Point> pl_keima_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> pl_gin_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> pl_kin_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> pl_hisha_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> pl_kaku_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> pl_ryu_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> pl_uma_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> pl_ou_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> ai_hu_wcm(KOMA_TYPE **ban, Point point);
std::vector<Point> ai_kyousha_wcm(KOMA_TYPE **ban, Point point);
std::vector<Point> ai_keima_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> ai_gin_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> ai_kin_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> ai_hisha_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> ai_kaku_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> ai_ou_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> ai_ryu_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> ai_uma_wcm(KOMA_TYPE **ban, Point p);
std::vector<Point> tegoma_wcm(KOMA_TYPE **main_ban, Point p);
int EVAL(Node *node);
void PLAYER_EXPAND(Node *node);
void EXPAND(Node *node);
Node *ai_turn(Node *root);
i64_t max(Node *node, i64_t alpha, i64_t beta, u8_t limit);
i64_t min(Node *node, i64_t alpha, i64_t beta, u8_t limit);
std::vector<Point> nihu_wcm(KOMA_TYPE **main_ban);
std::vector<Point> ai_nihu_wcm(KOMA_TYPE **main_ban);
u8_t ai_targetable(KOMA_TYPE **ban, u8_t x, u8_t y, std::vector<Point>  *points);
u8_t pl_targetable(KOMA_TYPE **ban, u8_t x, u8_t y, std::vector<Point>  *points);

#endif
