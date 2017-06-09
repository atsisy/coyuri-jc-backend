//#include "types.hpp"
//
//MochiGoma::MochiGoma() {
//	tegoma = new KOMA_TYPE[_MOCHIGOMA_LIMIT];
//	for (u8_t i = 0; i < _MOCHIGOMA_LIMIT; ++i) {
//		tegoma[i] = EMPTY;
//	}
//	pointer = 0;
//}
//
//MochiGoma::MochiGoma(MochiGoma *mochi) {
//	tegoma = new KOMA_TYPE[_MOCHIGOMA_LIMIT];
//	i8_t i;
//	for (i = 0; i < _MOCHIGOMA_LIMIT; ++i) {
//		tegoma[i] = EMPTY;
//	}
//
//	for (i = 0; i < _MOCHIGOMA_LIMIT && mochi->get_elem(i) != EMPTY;++i) {
//		tegoma[i] = mochi->get_elem(i);
//	}
//
//	/*
//	
//	do {
//		++i;
//		tegoma[i] = mochi->tegoma[i];
//	} while (tegoma[i] != EMPTY);*/
//	pointer = 0;
//}
//
//MochiGoma::~MochiGoma() {
//	delete[] tegoma;
//}
//
//void MochiGoma::push(KOMA_TYPE type) {
//	tegoma[pointer] = type;
//	++pointer;
//}
//
//KOMA_TYPE MochiGoma::get_elem(i8_t index) {
//	return tegoma[index];
//}