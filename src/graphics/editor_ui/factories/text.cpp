#include "text.hpp"
#include "graphics/editor_ui/widgets/text.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Own_Ptr<Text> Text::make(const Font& font, const String& text)
{
	return make_own_ptr<Text>(font, text);
}

Text::Text(const Font& font, const String& text) :
	m_font{font},
	m_text{text}
{
}

Own_Ptr<Widget> Text::make_widget()
{
	return make_own_ptr<Widgets::Text>(m_text, m_font);
}

}
