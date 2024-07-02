#include "image.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"

namespace UI
{

Image::Image(Layout&& layout) :
	Widget{(Layout&&)layout}
{
}

void Image::draw_impl(Recti parent_area, float opacity, float)
{
	sprite.draw(parent_area, opacity);
}

Widget_Ptr Image::clone_impl(Layout&& layout) const
{
	Own_Ptr<Image> cloned = make_own_ptr<Image>((Layout&&)layout);
	cloned->sprite = this->sprite;
	return cloned;
}

}
