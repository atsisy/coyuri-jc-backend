#include <iostream>
#include <fstream>
#include <sstream>
#include <types.hpp>
#include "prot.hpp"
#include <stdio.h>
#include <map>
#include <functional>

std::map<u64_t, std::function<std::vector<Point>(KOMA_TYPE **, Point)> > function_table;
std::map<u64_t, u64_t> naru_map;
std::map<KOMA_TYPE, int> koma_to_index;
void map_init();
void print_data(Node *result, const char *file_name);

int run_coyuri(int argc, char **argv) {

	Node *node;
	
	map_init();

	CoyuriIniter initer;
	initer.init(argv[1], &node);
	
	print_data(ai_turn(node), argv[2]);
	
}

void map_init() {
	function_table.insert(std::make_pair(EMPTY, null_wcm));
	function_table.insert(std::make_pair(HU, pl_hu_wcm));
	function_table.insert(std::make_pair(KYOUSHA, pl_kyousha_wcm));
	function_table.insert(std::make_pair(KEIMA, pl_keima_wcm));
	function_table.insert(std::make_pair(GIN, pl_gin_wcm));
	function_table.insert(std::make_pair(KIN, pl_kin_wcm));
	function_table.insert(std::make_pair(HISHA, pl_hisha_wcm));
	function_table.insert(std::make_pair(KAKU, pl_kaku_wcm));
	function_table.insert(std::make_pair(TOKIN, pl_kin_wcm));
	function_table.insert(std::make_pair(NARIKYOU, pl_kin_wcm));
	function_table.insert(std::make_pair(NARIKEI, pl_kin_wcm));
	function_table.insert(std::make_pair(NARIGIN, pl_kin_wcm));
	function_table.insert(std::make_pair(RYU, pl_ryu_wcm));
	function_table.insert(std::make_pair(UMA, pl_uma_wcm));
	function_table.insert(std::make_pair(OU, pl_ou_wcm));
	function_table.insert(std::make_pair(EN_HU, ai_hu_wcm));
	function_table.insert(std::make_pair(EN_KYOUSHA, ai_kyousha_wcm));
	function_table.insert(std::make_pair(EN_KEIMA, ai_keima_wcm));
	function_table.insert(std::make_pair(EN_GIN, ai_gin_wcm));
	function_table.insert(std::make_pair(EN_KIN, ai_kin_wcm));
	function_table.insert(std::make_pair(EN_HISHA, ai_hisha_wcm));
	function_table.insert(std::make_pair(EN_KAKU, ai_kaku_wcm));
	function_table.insert(std::make_pair(EN_TOKIN, ai_kin_wcm));
	function_table.insert(std::make_pair(EN_NARIKYOU, ai_kin_wcm));
	function_table.insert(std::make_pair(EN_NARIKEI, ai_kin_wcm));
	function_table.insert(std::make_pair(EN_NARIGIN, ai_kin_wcm));
	function_table.insert(std::make_pair(EN_RYU, ai_ryu_wcm));
	function_table.insert(std::make_pair(EN_UMA, ai_uma_wcm));
	function_table.insert(std::make_pair(EN_OU, ai_ou_wcm));

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

	koma_to_index.insert(std::make_pair(EMPTY, 0));
	koma_to_index.insert(std::make_pair(HU, 2));
	koma_to_index.insert(std::make_pair(KYOUSHA, 3));
	koma_to_index.insert(std::make_pair(KEIMA, 4));
	koma_to_index.insert(std::make_pair(GIN, 5));
	koma_to_index.insert(std::make_pair(KIN, 6));
	koma_to_index.insert(std::make_pair(HISHA, 7));
	koma_to_index.insert(std::make_pair(KAKU, 8));
	koma_to_index.insert(std::make_pair(TOKIN, 9));
	koma_to_index.insert(std::make_pair(NARIKYOU, 10));
	koma_to_index.insert(std::make_pair(NARIKEI, 11));
	koma_to_index.insert(std::make_pair(NARIGIN, 12));
	koma_to_index.insert(std::make_pair(RYU, 13));
	koma_to_index.insert(std::make_pair(UMA, 14));
	koma_to_index.insert(std::make_pair(OU, 15));
	koma_to_index.insert(std::make_pair(EN_HU, 16));
	koma_to_index.insert(std::make_pair(EN_KYOUSHA, 17));
	koma_to_index.insert(std::make_pair(EN_KEIMA, 18));
	koma_to_index.insert(std::make_pair(EN_GIN, 19));
	koma_to_index.insert(std::make_pair(EN_KIN, 20));
	koma_to_index.insert(std::make_pair(EN_HISHA, 21));
	koma_to_index.insert(std::make_pair(EN_KAKU, 22));
	koma_to_index.insert(std::make_pair(EN_TOKIN, 23));
	koma_to_index.insert(std::make_pair(EN_NARIKYOU, 24));
	koma_to_index.insert(std::make_pair(EN_NARIKEI, 25));
	koma_to_index.insert(std::make_pair(EN_NARIGIN, 26));
	koma_to_index.insert(std::make_pair(EN_RYU, 27));
	koma_to_index.insert(std::make_pair(EN_UMA, 28));
	koma_to_index.insert(std::make_pair(EN_OU, 29));
}

void print_data(Node *result, const char *file_name){

	FILE *result_file = fopen(file_name, "w");

	for (u8_t y = 0;y < 9;y++) {
		for (u8_t x = 0; x < 9; ++x) {
			fprintf(result_file, "%d ", koma_to_index.at(result->get_banmen()->get_banmen()[x][y]));
			printf("%d ", koma_to_index.at(result->get_banmen()->get_banmen()[x][y]));
		}
		fprintf(result_file, "\n");
		printf("\n");
	}
	
	fprintf(result_file, "ai_mochi ");
	printf("ai_mochi ");
	for (KOMA_TYPE type : *result->ai_mochigoma) {
		if (!type) {
			continue;
		}
		fprintf(result_file, "%d ", koma_to_index.at(type));
		printf("%d ", koma_to_index.at(type));
	}
	fprintf(result_file, "\n");
	printf("\n");

	fprintf(result_file, "pl_mochi ");
	printf("pl_mochi ");
	for (KOMA_TYPE type : *result->pl_mochigoma) {
		if (!type) {
			continue;
		}
		fprintf(result_file, "%d ", koma_to_index.at(type));
		printf("%d ", koma_to_index.at(type));
	}
	fprintf(result_file, "\n");

	fclose(result_file);
}
