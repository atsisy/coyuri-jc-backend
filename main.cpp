#include <iostream>
#include <fstream>
#include <sstream>
#include "types.hpp"
#include "prot.hpp"
#include <stdio.h>
#include <stdlib.h>

Tegoma *player_tegomas[6][6];
Tegoma *ai_tegomas[6][6];
KOMA_TYPE UTSU;
Point UTSU_KOMA;

std::vector<Point> (*wcm_ftable[])(KOMA_TYPE **ban, Point point) = {
	null_wcm,
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
	ai_ou_wcm,
	tegoma_wcm
};

void load_src(const char *file_name, BANMEN *ban);
void print_data(Node *result, const char *file_name);

int main(int argc, char **argv) {
	BANMEN *ban = new BANMEN;
      load_src(argv[1], ban);
	print_data(ai_turn(new Node(ban, NULL)), argv[2]);
}

void print_data(Node *result, const char *file_name){
	FILE *result_file = fopen(file_name, "w");

	for (u8_t y = 0;y < 9;y++) {
		for (u8_t x = 0; x < 9; ++x) {
			fprintf(result_file, "%d ", result->get_banmen()->get_banmen()[x][y]);
			printf("%d ", result->get_banmen()->get_banmen()[x][y]);
		}
		fprintf(result_file, "\n");
		printf("\n");
	}
	fclose(result_file);
}

void load_src(const char *file_name, BANMEN *ban) {

      i64_t i_t_i;
	std::ifstream ifs(file_name);
	if (ifs.fail()){
		std::cerr << "FAILD" << std::endl;
		exit(0);
	}
      std::string str;

      std::getline(ifs, str);
      /*
       *strの中身である、手数は今の所使わないので捨てる
       */
      
	for (u8_t y = 0;y < 9;++y) {
            std::getline(ifs, str);
            std::stringstream ss(str);

		for (u8_t x = 0; x < 9; ++x) {
                  ss >> i_t_i;
			ban->set_type(x, y, (KOMA_TYPE)i_t_i);
		}
	}
      
}

