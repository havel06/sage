#include "size.hpp"

namespace UI
{


int Size::to_pixels(Vec2i parent_size) const
{
	return (parent_width * parent_size.x) + (parent_height * parent_size.y) + pixels;
}

Size Size::lerp(const Size& other, float amount)
{
	return Size {
		.automatic = this->automatic || other.automatic,
		.pixels = this->pixels + (int)((this->pixels - other.pixels) * amount),
		.parent_width = this->parent_width + (this->parent_width - other.parent_width) * amount,
		.parent_height = this->parent_height + (this->parent_height - other.parent_height) * amount,
	};
}

}
