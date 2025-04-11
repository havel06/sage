#include "input_integer.hpp"
#include "graphics/editor_ui/widgets/input.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Input_Integer* Input_Integer::make(Widgets::Input_State& state, const Font& font, const String& label)
{
	return new Input_Integer(state, font, label);
}

Input_Integer::Input_Integer(Widgets::Input_State& state, const Font& font, const String& label) :
	m_state{state},
	m_font{font},
	m_label{label}
{
}

Input_Integer* Input_Integer::with_value(int value)
{
	m_value = value;
	return this;
}

Input_Integer* Input_Integer::on_edit(Function_Wrapper<void(bool valid, int val)>&& callback)
{
	m_on_edit = move(callback);
	return this;
}

Input_Integer* Input_Integer::on_enter(Function_Wrapper<void(bool valid, int val)>&& callback)
{
	m_on_enter = move(callback);
	return this;
}

Own_Ptr<Widget> Input_Integer::make_widget()
{
	auto input = make_own_ptr<Widgets::Input>(m_font, m_label, m_state, make_own_ptr<Widgets::Input_Constraint_Integer>());

	input->on_edit = [input=input.get(), state=&m_state, callback=m_on_edit] () mutable {
		callback(input->is_valid(), atoi(state->get_content().data()));
	};

	input->on_enter = [input=input.get(), state=&m_state, callback=m_on_enter] () mutable {
		callback(input->is_valid(), atoi(state->get_content().data()));
	};

	if (m_value.has_value())
		m_state.set_content(String::from_int(m_value.value()));

	return input;
}

}
