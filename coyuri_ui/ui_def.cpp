#include "ui_types.hpp"

Image::Image(const TCHAR *file_name)
{
	this->image_handle = LoadGraph(file_name);
}