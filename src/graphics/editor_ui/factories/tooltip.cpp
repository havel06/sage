#include "tooltip.hpp"
#include "graphics/editor_ui/widgets/tooltip.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Tooltip* Tooltip::make(const String& text, const Font& font, Own_Ptr<Widget_Factory>&& child)
{
	return new Tooltip(text, font, move(child));
}

Tooltip::Tooltip(const String& text, const Font& font, Own_Ptr<Widget_Factory>&& child) :
	m_text{text},
	m_font{font},
	m_child{move(child)}
{
}

Own_Ptr<Widget> Tooltip::make_widget()
{
	return make_own_ptr<Widgets::Tooltip>(m_child->make_widget(), m_text, m_font);
}

}
