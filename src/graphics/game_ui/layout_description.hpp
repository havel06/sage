#pragma once
#include "size.hpp"
#include "utils/array.hpp"

namespace Game_UI
{

struct Layout_Description
{
	Array<Size> rows;
	Array<Size> columns;
};

}
