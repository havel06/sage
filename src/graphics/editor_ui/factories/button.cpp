#include "button.hpp"
#include "graphics/editor_ui/widgets/button.hpp"
#include "utils/own_ptr.hpp"
#include "utils/move.hpp"

namespace Editor_UI::Factories
{

Own_Ptr<Button> Button::make(Function_Wrapper<void()>&& callback)
{
	return make_own_ptr<Button>(move(callback));
}

Button::Button(Function_Wrapper<void()>&& callback) :
	m_callback{move(callback)}
{
}

Button& Button::with_icon(const Icon_Resource& icon)
{
	m_icon = &icon;
	return *this;
}

Button& Button::with_text(const Font& font, const String& text)
{
	m_font = &font;
	m_text = text;
	return *this;
}

Own_Ptr<Widget> Button::make_widget()
{
	auto button = make_own_ptr<Widgets::Button>(m_font, m_text, m_icon);

	// Icon button
	if (m_icon && !m_font) {
		button->transparent = true;
		button->narrow = true;
	}

	return button;
}

}
