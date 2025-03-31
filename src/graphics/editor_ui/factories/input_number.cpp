#include "input_number.hpp"
#include "graphics/editor_ui/widgets/input.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Input_Number* Input_Number::make(const Font& font, const String& label)
{
	return new Input_Number(font, label);
}

Input_Number::Input_Number(const Font& font, const String& label) :
	m_font{font},
	m_label{label}
{
}

Input_Number* Input_Number::with_value(float value)
{
	m_value = value;
	return this;
}

Input_Number* Input_Number::on_edit(Function_Wrapper<void(bool, float)>&& callback)
{
	m_on_edit = move(callback);
	return this;
}

Input_Number* Input_Number::on_enter(Function_Wrapper<void(bool, float)>&& callback)
{
	m_on_enter = move(callback);
	return this;
}

Own_Ptr<Widget> Input_Number::make_widget()
{
	auto input = make_own_ptr<Widgets::Input>(m_font, m_label, make_own_ptr<Widgets::Input_Constraint_Number>());

	input->on_edit = [this_ptr=input.get(), callback=m_on_edit] () mutable {
		callback(this_ptr->is_valid(), atof(this_ptr->get_content().data()));
	};

	input->on_enter = [this_ptr=input.get(), callback=m_on_enter] () mutable {
		callback(this_ptr->is_valid(), atof(this_ptr->get_content().data()));
	};

	if (m_value.has_value())
		input->set_content(String::from_float(m_value.value()));

	return input;
}

}
