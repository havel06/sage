#include "input_text.hpp"
#include "graphics/editor_ui/widgets/input.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Input_Text* Input_Text::make(Widgets::Input_State& state, const Font& font, const String& label)
{
	return new Input_Text(state, font, label);
}

Input_Text::Input_Text(Widgets::Input_State& state, const Font& font, const String& label) :
	m_state{state},
	m_font{font},
	m_label{label}
{
}

Input_Text* Input_Text::content(const String& content)
{
	m_default_content = content;
	return this;
}

Input_Text* Input_Text::on_edit(Function_Wrapper<void(const String&)>&& callback)
{
	m_on_edit = move(callback);
	return this;
}

Input_Text* Input_Text::on_enter(Function_Wrapper<void(const String&)>&& callback)
{
	m_on_enter = move(callback);
	return this;
}

Input_Text* Input_Text::with_hints(const Array<String>& hints)
{
	m_hints = hints;
	return this;
}

Own_Ptr<Widget> Input_Text::make_widget()
{
	auto input = make_own_ptr<Widgets::Input>(m_font, m_label, m_state, make_own_ptr<Widgets::Input_Constraint_None>());

	input->on_edit = [state=&m_state, callback=m_on_edit] () mutable {
		callback(state->get_content());
	};

	input->on_enter = [state=&m_state, callback=m_on_enter] () mutable {
		callback(state->get_content());
	};

	if (m_default_content.has_value())
		m_state.set_content(m_default_content.value());
	m_state.set_hints(m_hints);

	return input;
}

}
