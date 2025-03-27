#include "input_integer.hpp"
#include "graphics/editor_ui/widgets/input.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Input_Integer* Input_Integer::make(const Font& font, const String& label)
{
	return new Input_Integer(font, label);
}

Input_Integer::Input_Integer(const Font& font, const String& label) :
	m_font{font},
	m_label{label}
{
}

Input_Integer* Input_Integer::on_edit(Function_Wrapper<void(int)>&& callback)
{
	m_on_edit = move(callback);
	return this;
}

Input_Integer* Input_Integer::on_enter(Function_Wrapper<void(int)>&& callback)
{
	m_on_enter = move(callback);
	return this;
}

Own_Ptr<Widget> Input_Integer::make_widget()
{
	auto input = make_own_ptr<Widgets::Input>(m_font, m_label, make_own_ptr<Widgets::Input_Constraint_Integer>());
	input->on_edit = [this_ptr=input.get(), callback=m_on_edit] () mutable { callback(atoi(this_ptr->get_content().data())); };
	input->on_enter = [this_ptr=input.get(), callback=m_on_enter] () mutable { callback(atoi(this_ptr->get_content().data())); };
	return input;
}

}
