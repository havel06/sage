#include "input_number.hpp"
#include "graphics/editor_ui/widgets/input.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Input_Number::Input_Number(const Font& font, const String& label) :
	m_font{font},
	m_label{label}
{
}

Input_Number& Input_Number::on_edit(Function_Wrapper<void(float)>&& callback)
{
	m_on_edit = move(callback);
	return *this;
}

Input_Number& Input_Number::on_enter(Function_Wrapper<void(float)>&& callback)
{
	m_on_enter = move(callback);
	return *this;
}

Own_Ptr<Widget> Input_Number::make_widget()
{
	auto input = make_own_ptr<Widgets::Input>(m_font, m_label, make_own_ptr<Widgets::Input_Constraint_Number>());
	input->on_edit = [this_ptr=input.get(), callback=m_on_edit] () mutable { callback(atof(this_ptr->get_content().data())); };
	input->on_enter = [this_ptr=input.get(), callback=m_on_enter] () mutable { callback(atof(this_ptr->get_content().data())); };
	return input;
}

}
