#include "button.hpp"
#include "../widgets/button.hpp"

namespace Game_UI {

Button_Factory::Button_Factory()
{
	register_parameter("normal", m_widget_normal);
	register_parameter("focused", m_widget_focused);
}

Own_Ptr<Widget> Button_Factory::make_widget(Layout&& layout)
{
	return make_own_ptr<Button>(m_widget_normal.value->make_widget(), m_widget_focused.value->make_widget(), move(layout));
}

}
