#pragma once

#include "types.hpp"
#include "DxLib.h"
#include "types.hpp"

class Image {

private:
	 i64_t image_handle;

public:
	Image(const TCHAR *file_name);
	void draw(i64_t x, i64_t y);

};

class GraphicalBanmen {
	
private:
	KOMA_TYPE banmen[9][9];

public:
	GraphicalBanmen();
	void redraw();

};