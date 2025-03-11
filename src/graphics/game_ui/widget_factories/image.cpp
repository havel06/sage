#include "image.hpp"
#include "../widgets/image.hpp"

namespace Game_UI {

Image_Factory::Image_Factory()
{
	register_parameter("sprite", m_sprite);
}

Own_Ptr<Widget> Image_Factory::make_widget(Layout&& layout)
{
	Own_Ptr<Image> widget = make_own_ptr<Image>(move(layout));
	widget->sprite = m_sprite.value;
	return widget;
}

}
