#include <iostream>
#include <fstream>
#include <sstream>
#include <types.hpp>
#include "prot.hpp"
#include <stdio.h>
#include <map>
#include <functional>
#include "coutil.hpp"
#include <iostream>

std::map<KOMA_TYPE, KOMA_TYPE> naru_map;

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
void print_data(Node *result, const char *file_name);

//#define _ENABLE_COUTIL_TIMER

int main(int argc, char **argv) {

#ifdef _ENABLE_COUTIL_TIMER
	cut::clock clock;
	clock.start();

#endif

	Node *node;
	
	map_init();

	CoyuriIniter initer;
	initer.init(argv[1], &node);
	
	print_data(ai_turn(node), argv[2]);

#ifdef _ENABLE_COUTIL_TIMER
	std::cout << "\ntime->" <<  clock.stop() << "ms" << std::endl;
#endif

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

}

void print_data(Node *result, const char *file_name){

	FILE *result_file = fopen(file_name, "w");

	for (u8_t y = 0;y < 9;y++) {
		for (u8_t x = 0; x < 9; ++x) {
			if (_IS_EMPTY(result->get_banmen()->get_banmen()[x][y]))
			{
				fprintf(result_file, "0 ");
				printf("0 ");
			}
			else {
				fprintf(result_file, "%d ", (result->get_banmen()->get_banmen()[x][y] >> 1) + 1);
				printf("%d ", (result->get_banmen()->get_banmen()[x][y] >> 1) + 1);
			}
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
		fprintf(result_file, "%d ", (type >> 1) + 1);
		printf("%d ", (type >> 1) + 1);
	}
	fprintf(result_file, "\n");
	printf("\n");

	fprintf(result_file, "pl_mochi ");
	printf("pl_mochi ");
	for (KOMA_TYPE type : *result->pl_mochigoma) {
		if (!type) {
			continue;
		}
		fprintf(result_file, "%d ", (type >> 1) + 1);
		printf("%d ", (type >> 1) + 1
		);
	}
	fprintf(result_file, "\n");

	fclose(result_file);
}
