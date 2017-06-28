#include <iostream>
#include <fstream>
#include <sstream>
#include <types.hpp>
#include "prot.hpp"
#include <stdio.h>
#include <functional>
#include "coutil.hpp"
#include <iostream>
#include <unordered_map>

std::unordered_map<KOMA_TYPE, KOMA_TYPE> naru_map;
u64_t teban_number;
extern i64_t E_VALUE_ARRAY[29];

#define _D

std::function<std::vector<Point>(KOMA_TYPE **, Point)> wcm_function_table[] = {
	null_wcm,
	pl_hu_wcm,
	pl_kyousha_wcm,
	pl_keima_wcm,
	pl_gin_wcm,
	pl_kin_wcm,
	pl_hisha_wcm,
	pl_kaku_wcm,
	pl_kin_wcm,
	pl_kin_wcm,
	pl_kin_wcm,
	pl_kin_wcm,
	pl_ryu_wcm,
	pl_uma_wcm,
	pl_ou_wcm,
	ai_hu_wcm,
	ai_kyousha_wcm,
	ai_keima_wcm,
	ai_gin_wcm,
	ai_kin_wcm,
	ai_hisha_wcm,
	ai_kaku_wcm,
	ai_kin_wcm,
	ai_kin_wcm,
	ai_kin_wcm,
	ai_kin_wcm,
	ai_ryu_wcm,
	ai_uma_wcm,
	ai_ou_wcm
};

void map_init();


int main(int argc, char **argv) {
	
	Node *node;
	
	map_init();

	CoyuriIniter initer;
	initer.init(argv[1], &node, &teban_number);

	CoyuriNegaScout searcher(node, teban_number);
	searcher.start();

	searcher.print(argv[2]);

}

void map_init() {

	naru_map.insert(std::make_pair(EMPTY, EMPTY));
	naru_map.insert(std::make_pair(HU, TOKIN));
	naru_map.insert(std::make_pair(KYOUSHA, NARIKEI));
	naru_map.insert(std::make_pair(KEIMA, NARIKEI));
	naru_map.insert(std::make_pair(GIN, NARIGIN));
	naru_map.insert(std::make_pair(KIN, KIN));
	naru_map.insert(std::make_pair(HISHA, RYU));
	naru_map.insert(std::make_pair(KAKU, UMA));
	naru_map.insert(std::make_pair(TOKIN, TOKIN));
	naru_map.insert(std::make_pair(NARIKYOU, NARIKYOU));
	naru_map.insert(std::make_pair(NARIKEI, NARIKEI));
	naru_map.insert(std::make_pair(NARIGIN, NARIGIN));
	naru_map.insert(std::make_pair(RYU, RYU));
	naru_map.insert(std::make_pair(UMA, UMA));
	naru_map.insert(std::make_pair(OU, OU));
	naru_map.insert(std::make_pair(EN_HU, EN_TOKIN));
	naru_map.insert(std::make_pair(EN_KYOUSHA, EN_NARIKEI));
	naru_map.insert(std::make_pair(EN_KEIMA, EN_NARIKEI));
	naru_map.insert(std::make_pair(EN_GIN, EN_NARIGIN));
	naru_map.insert(std::make_pair(EN_KIN, EN_KIN));
	naru_map.insert(std::make_pair(EN_HISHA, EN_RYU));
	naru_map.insert(std::make_pair(EN_KAKU, EN_UMA));
	naru_map.insert(std::make_pair(EN_TOKIN, EN_TOKIN));
	naru_map.insert(std::make_pair(EN_NARIKYOU, EN_NARIKYOU));
	naru_map.insert(std::make_pair(EN_NARIKEI, EN_NARIKEI));
	naru_map.insert(std::make_pair(EN_NARIGIN, EN_NARIGIN));
	naru_map.insert(std::make_pair(EN_RYU, EN_RYU));
	naru_map.insert(std::make_pair(EN_UMA, EN_UMA));
	naru_map.insert(std::make_pair(EN_OU, EN_OU));

#ifdef _D
	cut::json_parser eval_json("C:\\Users\\Akihiro\\Desktop\\coyuri_eval.json");
#endif
#ifndef _D
	cut::json_parser eval_json("./coyuri_eval.json");
#endif
	E_VALUE_ARRAY[0] = 0;

	E_VALUE_ARRAY[1] = eval_json.get_value<i64_t>("Eval.PL_HU");
	E_VALUE_ARRAY[2] = eval_json.get_value<i64_t>("Eval.PL_KYOUSHA");
	E_VALUE_ARRAY[3] = eval_json.get_value<i64_t>("Eval.PL_KEIMA");
	E_VALUE_ARRAY[4] = eval_json.get_value<i64_t>("Eval.PL_GIN");
	E_VALUE_ARRAY[5] = eval_json.get_value<i64_t>("Eval.PL_KIN");
	E_VALUE_ARRAY[6] = eval_json.get_value<i64_t>("Eval.PL_HISHA");
	E_VALUE_ARRAY[7] = eval_json.get_value<i64_t>("Eval.PL_KAKU");
	E_VALUE_ARRAY[8] = eval_json.get_value<i64_t>("Eval.PL_OU");
	E_VALUE_ARRAY[9] = eval_json.get_value<i64_t>("Eval.PL_TOKIN");
	E_VALUE_ARRAY[10] = eval_json.get_value<i64_t>("Eval.PL_NARIKYOU");
	E_VALUE_ARRAY[11] = eval_json.get_value<i64_t>("Eval.PL_NARIKEI");
	E_VALUE_ARRAY[12] = eval_json.get_value<i64_t>("Eval.PL_NARIGIN");
	E_VALUE_ARRAY[13] = eval_json.get_value<i64_t>("Eval.PL_RYU");
	E_VALUE_ARRAY[14] = eval_json.get_value<i64_t>("Eval.PL_UMA");

	E_VALUE_ARRAY[15] = eval_json.get_value<i64_t>("Eval.AI_HU");
	E_VALUE_ARRAY[16] = eval_json.get_value<i64_t>("Eval.AI_KYOUSHA");
	E_VALUE_ARRAY[17] = eval_json.get_value<i64_t>("Eval.AI_KEIMA");
	E_VALUE_ARRAY[18] = eval_json.get_value<i64_t>("Eval.AI_GIN");
	E_VALUE_ARRAY[19] = eval_json.get_value<i64_t>("Eval.AI_KIN");
	E_VALUE_ARRAY[20] = eval_json.get_value<i64_t>("Eval.AI_HISHA");
	E_VALUE_ARRAY[21] = eval_json.get_value<i64_t>("Eval.AI_KAKU");
	E_VALUE_ARRAY[22] = eval_json.get_value<i64_t>("Eval.AI_OU");
	E_VALUE_ARRAY[23] = eval_json.get_value<i64_t>("Eval.AI_TOKIN");
	E_VALUE_ARRAY[24] = eval_json.get_value<i64_t>("Eval.AI_NARIKYOU");
	E_VALUE_ARRAY[25] = eval_json.get_value<i64_t>("Eval.AI_NARIKEI");
	E_VALUE_ARRAY[26] = eval_json.get_value<i64_t>("Eval.AI_NARIGIN");
	E_VALUE_ARRAY[27] = eval_json.get_value<i64_t>("Eval.AI_RYU");
	E_VALUE_ARRAY[28] = eval_json.get_value<i64_t>("Eval.AI_UMA");
}

//void print_data(Node *result, const char *file_name){
//
//	FILE *result_file = fopen(file_name, "w");
//
//	for (u8_t y = 0;y < 9;y++) {
//		for (u8_t x = 0; x < 9; ++x) {
//			if (_IS_EMPTY(result->get_banmen()->get_banmen()[x][y]))
//			{
//				fprintf(result_file, "0 ");
//				printf("0 ");
//			}
//			else {
//				fprintf(result_file, "%d ", (result->get_banmen()->get_banmen()[x][y] >> 1) + 1);
//				printf("%d ", (result->get_banmen()->get_banmen()[x][y] >> 1) + 1);
//			}
//		}
//		fprintf(result_file, "\n");
//		printf("\n");
//	}
//	
//	fprintf(result_file, "ai_mochi ");
//	printf("ai_mochi ");
//	for (KOMA_TYPE type : *result->ai_mochigoma) {
//		if (!type) {
//			continue;
//		}
//		fprintf(result_file, "%d ", (type >> 1) + 1);
//		printf("%d ", (type >> 1) + 1);
//	}
//	fprintf(result_file, "\n");
//	printf("\n");
//
//	fprintf(result_file, "pl_mochi ");
//	printf("pl_mochi ");
//	for (KOMA_TYPE type : *result->pl_mochigoma) {
//		if (!type) {
//			continue;
//		}
//		fprintf(result_file, "%d ", (type >> 1) + 1);
//		printf("%d ", (type >> 1) + 1
//		);
//	}
//	fprintf(result_file, "\n");
//
//	fclose(result_file);
//}
