#include "image.hpp"

namespace Editor_UI::Widgets
{

Image::Image(const Sprite& sprite, Vec2i size)
{
	m_sprite = sprite;
	m_size = size;
}

void Image::draw()
{
	m_sprite.draw(Rectf{
		.position = m_position,
		.size = m_size
	});
}

Vec2i Image::layout(Recti bounding_box)
{
	// NOTE - bounding box size is ignored
	m_position = bounding_box.position;
	return m_size;
}


}
