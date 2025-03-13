#include "box.hpp"
#include "../widgets/box.hpp"

namespace Game_UI {

Box_Factory::Box_Factory()
{
	register_parameter("colour", m_colour);
}

Own_Ptr<Widget> Box_Factory::make_widget(Layout&& layout, const String& name, float fade_in_out_time)
{
	Own_Ptr<Box> widget = make_own_ptr<Box>(move(layout));
	widget->colour = m_colour.value;
	widget->set_name(String{name});
	widget->fade_in_out_time = fade_in_out_time;
	return widget;
}

}
