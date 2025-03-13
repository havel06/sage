#include "button.hpp"
#include "../widgets/button.hpp"
#include "utils/own_ptr.hpp"

namespace Game_UI {

Button_Factory::Button_Factory()
{
	register_parameter("normal", m_widget_normal);
	register_parameter("focused", m_widget_focused);
}

Own_Ptr<Widget> Button_Factory::make_widget(Layout&& layout, const String& name, float fade_in_out_time)
{
	Own_Ptr<Button> widget = make_own_ptr<Button>(
		m_widget_normal.value->make_widget(),
		m_widget_focused.value->make_widget(),
		move(layout)
	);

	widget->set_name(String{name});
	widget->fade_in_out_time = fade_in_out_time;

	return widget;
}

}
