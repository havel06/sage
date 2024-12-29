#include "colour.hpp"
#include <raylib/raylib.h>


Color Colour::to_ray_color() const
{
	return Color {
		.r = this->r,
		.g = this->g,
		.b = this->b,
		.a = this->a
	};
}
