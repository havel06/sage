#pragma once

#include "utils/vec2.hpp"

namespace UI
{


struct Size
{
	bool automatic = false; // If this is set to true, the values are ignored
	int pixels = 0;
	float parent_width = 0;
	float parent_height = 0;

	int to_pixels(Vec2i parent_size) const;
};


}
