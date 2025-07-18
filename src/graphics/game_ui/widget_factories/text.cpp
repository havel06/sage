#include "text.hpp"
#include "../widgets/text.hpp"

namespace Game_UI {

Text_Factory::Text_Factory(Font_Manager& font_manager) :
	m_font_manager{font_manager}
{
	register_parameter("font", m_font);
	register_parameter("text", m_text);
	register_parameter("size", m_size);
	register_parameter("align", m_align);
	register_parameter("colour", m_colour);
}

Own_Ptr<Widget> Text_Factory::make_widget(Layout&& layout, const String& name, float fade_in_out_time)
{
	Own_Ptr<Text> widget = make_own_ptr<Text>(m_font_manager.get(m_font.value, false), move(layout));
	widget->text = m_text.value;
	widget->size = m_size.value;
	widget->align = m_align.value;
	widget->colour = m_colour.value;
	widget->set_name(String{name});
	widget->fade_in_out_time = fade_in_out_time;
	return widget;
}

}
