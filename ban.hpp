#ifndef _BAN_HPP
#define _BAN_HPP

#include "types.hpp"

class Ban {

private:

	Masu *frontend_ban[9][9];
	KOMA_TYPE backend_ban[9][9];

public:

	Ban();

};

#endif