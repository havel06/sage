#include "image.hpp"
#include "utils/own_ptr.hpp"

namespace UI
{

Image::Image(Layout&& layout, Sprite&& sprite) :
	Widget{(Layout&&)layout}
{
	m_sprite = (Sprite&&)sprite;
}

void Image::draw_impl(Recti parent_area, float)
{
	m_sprite.draw(parent_area);
}

Widget_Ptr Image::clone_impl(Layout&& layout) const
{
	return make_own_ptr<Image>((Layout&&)layout, Sprite{m_sprite});
}

}
