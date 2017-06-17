#pragma once

#include "types.hpp"
#include "DxLib.h"

class Image {

private:
	 i64_t image_handle;

public:
	Image(const TCHAR *file_name);

};