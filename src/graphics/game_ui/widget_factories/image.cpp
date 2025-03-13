#include "image.hpp"
#include "../widgets/image.hpp"

namespace Game_UI {

Image_Factory::Image_Factory()
{
	register_parameter("sprite", m_sprite);
}

Own_Ptr<Widget> Image_Factory::make_widget(Layout&& layout, const String& name, float fade_in_out_time)
{
	Own_Ptr<Image> widget = make_own_ptr<Image>(move(layout));
	widget->sprite = m_sprite.value;
	widget->set_name(String{name});
	widget->fade_in_out_time = fade_in_out_time;
	return widget;
}

}
