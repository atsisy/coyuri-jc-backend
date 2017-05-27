#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cstdio>
#include <iomanip>

void update_score(bool flag) {
	std::remove("/home/annet/Documents/score.txt");
	std::ifstream back("/home/annet/Documents/score_back.txt");
	std::ofstream front("/home/annet/Documents/score.txt");
	std::string back_str;
	int win, lose;
	win = lose = 0;

	getline(back, back_str);

	std::stringstream stream(back_str);
	stream >> win >> lose;

	if (flag) {
		//AI‚ªŸ‚Á‚½
		front << "‚±‚ä‚è‚¿‚á‚ñ‚ÌíÑ" << std::endl;
		front << "Œ»İ" << std::to_string(win + 1) << "Ÿ" << std::to_string(lose) << "”s" << std::flush;
		back.close();
		std::remove("/home/annet/Documents/score_back.txt");
		std::ofstream new_back("/home/annet/Documents/score_back.txt");
		new_back << std::to_string(win + 1) << " " << std::to_string(lose) << std::flush;
		new_back.close();
	}
	else {
		//ƒvƒŒƒCƒ„[‚ªŸ‚Á‚½
		front << "‚±‚ä‚è‚¿‚á‚ñ‚ÌíÑ" << std::endl;
		front << "Œ»İ" << std::to_string(win) << "Ÿ" << std::to_string(lose + 1) << "”s" << std::flush;
		back.close();
		std::remove("/home/anneet/Documents/score_back.txt");
		std::ofstream new_back("/home/annet/Documents/score_back.txt");
		new_back << std::to_string(win) << " " << std::to_string(lose + 1) << std::flush;
		new_back.close();
	}
}

