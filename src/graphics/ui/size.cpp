#include "size.hpp"

namespace UI
{


int Size::to_pixels(Vec2i parent_size)
{
	return (parent_width * parent_size.x) + (parent_height * parent_size.y) + pixels;
}


}
