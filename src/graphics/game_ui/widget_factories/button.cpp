#include "button.hpp"
#include "../widgets/button.hpp"
#include "graphics/game_ui/widgets/box.hpp"
#include "utils/log.hpp"
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
		use_factory_or_fallback_widget(m_widget_normal.value),
		use_factory_or_fallback_widget(m_widget_focused.value),
		move(layout)
	);

	widget->set_name(String{name});
	widget->fade_in_out_time = fade_in_out_time;

	return widget;
}

Own_Ptr<Widget> Button_Factory::use_factory_or_fallback_widget(Own_Ptr<Widget_Factory>& factory)
{
	if (factory) {
		return factory->make_widget();
	} else {
		SG_WARNING("Button widget not set, using fallback widget.");
		return make_own_ptr<Box>(Layout{});
	}
}

}
