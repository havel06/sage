#include "image.hpp"
#include "graphics/editor_ui/widgets/image.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Own_Ptr<Image> Image::make(const Sprite& sprite, Vec2i size)
{
	return make_own_ptr<Image>(sprite, size);
}

Image::Image(const Sprite& sprite, Vec2i size) :
	m_sprite{sprite},
	m_size{size}
{
}

Own_Ptr<Widget> Image::make_widget()
{
	return make_own_ptr<Widgets::Image>(m_sprite, m_size);
}

}
