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
}

Own_Ptr<Widget> Text_Factory::make_widget()
{
	// FIXME - layout, children
	return make_own_ptr<Text>(m_font_manager.get(m_font.value, false), Layout{});
}

}
