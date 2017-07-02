#include "types.hpp"
#include "prot.hpp"
#include "file_reader.hpp"

extern i64_t E_VALUE_ARRAY[29];

void learn()
{
	cut::CsaLoader loader("C:\\Users\\Akihiro\\Desktop\\test.csa");
	loader.get_kif();
}